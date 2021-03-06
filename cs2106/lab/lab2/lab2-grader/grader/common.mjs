import { readFile as readFileCps } from 'fs';
import { promisify, inspect } from 'util';

const readFile = promisify(readFileCps);

const lineRegexes = {
  command: /----------command: (?<command>.+)$/m,
  commandBegin: /----------bfa06e76-6ffe-46aa-b71e-426bf7fb37f2-(?<index>\d+)-BEGIN----------$/m,
  commandEnd: /----------bfa06e76-6ffe-46aa-b71e-426bf7fb37f2-(?<index>\d+)-END----------$/m,
  exitcode: /----------exitcode: (?<exitcode>\d+)$/m,
  testeePid: /----------testeepid: (?<pid>\d+)$/m,
  execve: /(\[pid +(?<pid>\d+)\] )?execve\("(?<path>[^"]+?)", (?<argv>\["[^"]+?"(, ?"[^"]+?")*\])/m,
  wait: /(\[pid +(?<pid>\d+)\] )?wait4\((?<waitpid>\d+),/m,
  signaled: /(\[pid +(?<pid>\d+)\] )?\+\+\+ killed by (?<signal>SIG[A-Z]+)/m,
  info: /\[[^\S\r\n]*(?<pid>\d+)[^\S\r\n]*\][^\S\r\n]*(?<status>Exited)[^\S\r\n]+(?<exit_s>\d*)[^\S\r\n]*$/m,
  info_nonexit: /\[[^\S\r\n]*(?<pid>\d+)[^\S\r\n]*\][^\S\r\n]*(?<status>Running|Terminating)[^\S\r\n]*$/m,
  sigchld: /--- SIGCHLD {[^}]*?si_pid=(?<pid>\d+)[^}]*?} ---$/m,
  kill: /kill\((?<pid>-?\d+), (?<signal>[^)]+)/m,
  pass: /----------pass: (?<message>.+)$/m,
  fail: /----------fail: (?<message>.+)$/m,
  pids: /----------pids(?<pids>(?: \d+)*)$/m,
  logBegin: /----------logfile(?<index>\d+)-BEGIN----------$/m,
  logEnd: /----------logfile(?<index>\d+)-END----------$/m,
  logExpectedBegin: /----------logfile(?<index>\d+)-expected-BEGIN----------$/m,
  logExpectedEnd: /----------logfile(?<index>\d+)-expected-END----------$/m,
  readCommandFail: /Error while reading command; shutting down: (?<reason>.*)$/m,
  clone1: /clone\([^)]+\) = (?<pid>\d+)$/m,
  clone2: /<... clone resumed>, .+ = (?<pid>\d+)$/m
};

const signals = [
  "none",
  "SIGHUP",
  "SIGINT",
  "SIGQUIT",
  "SIGILL",
  "SIGTRAP",
  "SIGABRT",
  "SIGBUS",
  "SIGFPE",
  "SIGKILL",
  "SIGUSR1",
  "SIGSEGV",
  "SIGUSR2",
  "SIGPIPE",
  "SIGALRM",
  "SIGTERM",
  "SIGSTKFLT",
  "SIGCHLD",
  "SIGCONT",
  "SIGSTOP",
  "SIGTSTP",
  "SIGTTIN",
  "SIGTTOU",
  "SIGURG",
  "SIGXCPU",
  "SIGXFSZ",
  "SIGVTALRM",
  "SIGPROF",
  "SIGWINCH",
  "SIGIO",
  "SIGPWR",
  "SIGSYS"
];

function parseLine(line, lineIndex) {
  for (const [type, regex] of Object.entries(lineRegexes)) {
    const match = line.match(regex);
    if (!match) { continue; }
    const ret = { ...match.groups, type, raw: line, lineIndex };
    return ret;
  }
  return { type: "unknown", raw: line, lineIndex };
}

function splitTrace(trace) {
  return trace.split("\n").map(x => x.trim()).filter(x => x.length > 0).map(parseLine);
}

export function arrayEqual(a, b) {
  if (a === b) { return true; }
  if (!Array.isArray(a) || !Array.isArray(b)) { throw new Error("Non-array in arrayEqual"); }
  if (a.length !== b.length) { return false; }
  for (let i = 0; i < a.length; ++i) {
    if (a[i] !== b[i]) { return false; }
  }
  return true;
}

export class Trace {
  constructor(trace) {
    this.trace = trace;
    this.commands = [];
    this.logs = {};
    this.expectedLogs = {};

    let commandIndex = -1;
    let logLine = void 0;

    var infoIndex = 0;

    for (const line of this.trace) {
      if (['signaled', 'execve'].includes(line.type)) {
        line.isMainProcess = !line.pid || line.pid === this.testeePid;
      }

      if (typeof line.pid === 'string') {
        line.pid = parseInt(line.pid, 10);
      }
      if (typeof line.index === 'string') {
        line.index = parseInt(line.index, 10);
      }

      switch (line.type) {
      case 'testeePid': {
        if (this.testeePid) {
          throw new Error("More than 1 testeePid entry");
        }
        this.testeePid = line.pid;
        break;
      }

      case 'execve': {
        try {
          line.argv = JSON.parse(line.argv);
        } catch {
          line.argv = JSON.parse(line.argv.replaceAll('\\', '\\\\'))
        }
        if (line.path === './myshell' && arrayEqual(line.argv, ["./myshell","bfa06e76-6ffe-46aa-b71e-426bf7fb37f2"])) {
          line.type = 'launchSmExecve';
        }
        break;
      }

      case 'wait': {
        line.waitpid = parseInt(line.waitpid, 10);
        break;
      }

      case 'kill': {
        line.pid = parseInt(line.pid, 10);
        if (line.pid < 0) { line.pid = -line.pid; }
        break;
      }

      case 'command': {
        this.commands.push(line.command);
        break;
      }

      case 'info_nonexit': {
        if (line.status === 'Running') {
          line.running = 0;
        } else if (line.status === 'Terminating') {
          line.running = 2;
        } else {
          throw new Error("Unexpected status value");
        }
        line.commandIndex = commandIndex;
        line.type = 'info';
        line.infoIndex = infoIndex;
        infoIndex = infoIndex + 1;
        break;
      }

      case 'info': {
        line.running = 1;
        line.commandIndex = commandIndex;
        line.infoIndex = infoIndex;
        line.exit_s = parseInt(line.exit_s, 10);
        infoIndex = infoIndex + 1;
        break;
      }

      case 'signaled': {
        if (line.pid && line.pid !== this.testeePid) {
          continue;
        }

        if (this.signal) {
          throw new Error("More than 1 parent signaled entry");
        }
        this.signal = line.signal;
        break;
      }

      case 'exitcode': {
        if (this.exitcode) {
          throw new Error("More than 1 exitcode entry");
        }
        this.exitcode = parseInt(line.exitcode, 10);
        if (this.exitcode > 128 && this.exitcode < 128 + signals.length) {
          this.exitcodeSignal = signals[this.exitcode - 128];
        }
        break;
      }

      case 'commandBegin': {
        commandIndex = line.index;
        infoIndex = 0;
        break;
      }

      case 'commandEnd': {
        commandIndex = -1;
        break;
      }

      case 'pids': {
        line.pids = line.pids.trim().split(" ").flatMap(x => {
          const t = x.trim();
          if (t.length === 0) { return []; }
          const i = parseInt(t, 10);
          if (i === this.testeePid) { return []; }
          return [i];
        });
        line.pids
        break;
      }

      case 'logBegin':
      case 'logExpectedBegin': {
        if (logLine) {
          throw new Error(`Simultaneous log block? ${inspect(logLine)} ${inspect(line)}`);
        }
        logLine = line;
        logLine.lines = [];
        break;
      }

      case 'logEnd': {
        if (logLine.index != line.index) {
          throw new Error("Log block index start != end?");
        }
        this.logs[line.index] = logLine;
        logLine = void 0;
        break;
      }

      case 'logExpectedEnd': {
        if (logLine.index != line.index) {
          throw new Error("Log block index start != end?");
        }
        this.expectedLogs[line.index] = logLine;
        logLine = void 0;
        break;
      }

      case 'unknown': {
        if (logLine) {
          const trimmed = line.raw.trim();
          if (trimmed.length > 0) {
            logLine.lines.push(trimmed);
          }
        }
        break;
      }

      case 'readCommandFail': {
        this.readCommandFail = line.reason;
        break;
      }

      case 'clone1':
      case 'clone2':
        line.type = 'clone';
        break;

      }
    }
  }

  find(type, path) {
    return this.trace.find(line => line.type === type && !line.seen && line.path === path);
  }

  filter(type, path) {
    return this.trace.filter(line => line.type === type && !line.seen && line.path === path);
  }

  filterAllWaits() {
    return this.trace.filter(line => line.type === 'wait');
  }

  findExec(path) {
    return this.find('execve', path);
  }

  filterKills(signal) {
    return this.trace.filter(line => line.type === 'kill' && line.signal === signal);
  }

  filterExecs(path) {
    return this.filter('execve', path);
  }

  filterAllExecs() {
    return this.trace.filter(line => line.type === 'execve');
  }

  findInfo(command, index) {
    return this.trace.find(line => line.type === 'info' && line.commandIndex === command && line.infoIndex === index);
  }

  filterFails() {
    return this.trace.filter(line => line.type === 'fail').map(line => line.message);
  }

  filterPasses() {
    return this.trace.filter(line => line.type === 'pass');
  }

  hasRawLine(raw) {
    return this.trace.find(line => line.raw === raw) !== (void 0);
  }

  getUnseen(type) {
    return this.trace.filter(line => line.type === type && !line.seen);
  }

  getUnseenExecs() {
    return this.getUnseen('execve');
  }

  getUnseenInfos() {
    return this.getUnseen('info');
  }

  static fromString(trace) {
    return new Trace(splitTrace(trace));
  }

  static async fromFile(path) {
    return Trace.fromString(await readFile(path, "utf8"));
  }
}
