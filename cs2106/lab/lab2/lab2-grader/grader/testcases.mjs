import { createHash } from 'crypto';
import { arrayEqual } from './common.mjs';

Array.prototype.findLast = function (pred) {
  const t = this;
  for (let i = t.length - 1; i >= 0; --i) {
    if (pred(t[i])) {
      return t[i];
    }
  }
  return undefined;
};

const testcases = {};
export default testcases;

const F = "FACTOR";

const paths = {
  ch: "./...ch",
  ss: "./...ss",
  sl: "./...sl",
  sla: "./...sla",
  slb: "./...slb",
  slc: "./...slc",
  echo: "/bin/echo",
  sleep: "/bin/sleep",
  result: "./...res",
  lazy: "./...laz",
  pr: "./...pr",
  pw: "./...pw",
  rai: "./...rai",
  rib: "./...rib",
  rie: "./...rie",
  rio: "./...rio"
}

function sha256sumOutput(input) {
  const h = createHash('sha256');
  h.update(input, 'utf8');
  return `${h.digest('hex')}  -`;
}

function commandArgv(t, i) {
  if (i < t.commands.length) {
    return t.commands[i].split(" ");
  } else {
    return "";
  }
}

function joinComments(title, comments) {
  return `${title}: ${comments.join("; ")}`;
}

function equalAggregate(title, toMax, numResults, ...results) {
  const comments = [];
  const perResult = toMax / numResults;
  let seenResults = 0;
  let factor = 1;
  let totalScore = 0;
  for (const [score, max, comment] of results.filter(x => !!x)) {
    if (score === F) {
      factor *= max;
      comments.push(`*${max} penalty: ${comment}`);
      continue;
    }

    totalScore += (score / max) * perResult;
    if (comment) {
      comments.push(comment);
    }
    ++seenResults;
  }
  if (seenResults !== numResults) {
    totalScore = 0;
    // throw new Error(`Wrong number of results for ${title}, expected ${numResults}, got ${seenResults}`);
  }
  totalScore *= factor;
  totalScore = Math.min(Math.max(0, totalScore), toMax);
  if (totalScore < toMax || comments.length > 0) {
    return [totalScore, toMax, joinComments(title, comments)];
  }
  return [totalScore, toMax];
}

// EXERCISE 1A

function ex1CheckExec(t, ...argv) {
  // just remove the &
  if (argv[argv.length - 1] === "&") argv.pop();
  const path = argv[0];
  const exec = t.findExec(path);
  if (!exec) { return [0, 1, `Missing exec ${argv[0]}`]; }
  exec.seen = true;
  if (exec.isMainProcess) { return [-Infinity, 0, `Parent process exec-ed`]; }
  if (arrayEqual(exec.argv, argv)) { return [1, 1]; }
  const argvNoArgv0 = argv.slice(1);
  if (arrayEqual(exec.argv.slice(1), argvNoArgv0)) { return [0.75, 1, `Wrong argv[0] in exec ${argv[0]}`]; }
  if (arrayEqual(exec.argv.slice(1, argv.length - 1), argvNoArgv0)) { return [0.5, 1, `Extraneous arguments in exec ${argv[0]}`]; }
  if (arrayEqual(exec.argv.slice(0, argv.length - 1), argvNoArgv0)) { return [0.25, 1, `Missing argv[0] in exec ${argv[0]}`]; }
  return [0, 1, `Wrong exec ${exec.argv.join(" ")}`];
}

function isRunProgramCommand(c) {
  return c.startsWith("/") || c.startsWith(".")
}

function ex1CheckExecs(t) {
  return t.commands.filter(isRunProgramCommand).map(c => ex1CheckExec(t, ...c.split(" ")));
}

function ex1CheckExtraExecs(t) {
  if (t.getUnseenExecs().length > 0) {
    return [F, 0.5, "Extraneous execs seen"];
  }
  return null;
}

Object.assign(testcases, {
  '1a1': t => equalAggregate('1a1', 1, 1,
    ...ex1CheckExecs(t),
    ex1CheckExtraExecs(t)
  ),
  '1a2': t => equalAggregate('1a2', 1, 1,
    ...ex1CheckExecs(t),
    ex1CheckExtraExecs(t)
  ),
  '1a3': t => equalAggregate('1a3', 1, 1,
    (t.filterExecs(paths.sl).length === 1 && t.filterAllWaits().length === 1 && !t.trace.some(line => line.raw.startsWith('Timeout')))
      ? [1, 1]
      : [0, 1, "Extra exec/wait or timeout seen"]
  ),
  '1a4': t => equalAggregate('1a4', 1, 1,
    ...ex1CheckExecs(t),
    ex1CheckExtraExecs(t)
  ),
  '1b1': t => equalAggregate('1b1', 1, 3,
    ...ex1CheckExecs(t),
    ex1CheckExtraExecs(t)
  ),
  '1b2': t => equalAggregate('1b2', 1, 1,
    t.hasRawLine(`print-${commandArgv(t, 1)[1]}`)
      ? [1, 1]
      : [0, 1, "Expected output not seen"]
  ),
  '1b3': t => equalAggregate('1b3', 1, 1,
    t.hasRawLine(`${commandArgv(t, 0)[0]} not found`) && 
    t.hasRawLine(`${commandArgv(t, 1)[0]} not found`)
      ? [1, 1]
      : [0, 1, "Expected output not seen"],
    ex1CheckExtraExecs(t)
  ),
});

// Test info command

const statusString = {
  0: "Running",
  1: "Exited",
  2: "Terminated"
};

function checkInfo(t, c, index, p, expected, exit_s) {
  const info = t.findInfo(c, index);
  if (!info) { return [0, 1, `Missing info for ${p} at command index ${c}; Info=${info}`]; }
  const execs = t.filterExecs(p);
  if (execs.length == 0) { return [0, 1, `Missing exec ${p}`]; }
  if (info.running !== expected) { return [0, 1, `Expected ${statusString[expected]}, got ${statusString[info.running]} for ${p} at command index ${c}`]; }
  let found = false;
  for (const exec of execs) {
    if (info.pid === exec.pid) {
      found = true;
      break;
    }
  }
  if (!found) { return [0.5, 1, `Missing exec for PID for ${p} at command index ${c}; Info=${info.pid}`]; }
  if (expected === 1 && info.exit_s !== exit_s) { return [0.5, 1, `Wrong Exit Status for ${p} at command index ${c}; Expected=${exit_s}, Info=${info.exit_s}`]; }
  info.seen = true;
  return [1, 1];
}

function checkExtraInfo(t) {
  if (t.getUnseenInfos().length > 0) {
    return [F, 0.5, "Extraneous pids seen in info command"];
  }
  return null;
}

Object.assign(testcases, {
  '1c1': t => equalAggregate('1c1', 1, 2,
    checkInfo(t, 1, 0, paths.sleep, 0, 0),
    checkInfo(t, 2, 0, paths.sleep, 1, 0), 
    checkExtraInfo(t),
  ),
  '1c2': t => equalAggregate('1c2', 1, 5,
    checkInfo(t, 3, 1, paths.sleep, 1, 0),
    checkInfo(t, 4, 1, paths.sleep, 1, 0),
    checkInfo(t, 1, 0, paths.result, 1, 58),
    checkInfo(t, 3, 0, paths.result, 1, 58),
    checkInfo(t, 4, 0, paths.result, 1, 58), 
    checkExtraInfo(t)
  ),
  '1c3': t => equalAggregate('1c3', 1, 1,
    checkInfo(t, 1, 0, paths.sleep, 1, 1),
    checkExtraInfo(t)
  ),
  '2d1': t => equalAggregate('2d1', 1, 3,
    checkInfo(t, 1, 0, paths.sla, 1, 0),
    checkInfo(t, 1, 1, paths.slb, 1, 0),
    checkInfo(t, 1, 2, paths.slc, 1, 0), 
    checkExtraInfo(t)
  ),
  '2d2': t => equalAggregate('2d2', 1, 2,
    checkInfo(t, 1, 0, paths.sla, 1, 0),
    checkInfo(t, 1, 1, paths.result, 1, 255), 
    checkExtraInfo(t)
  ),
  '2d3': t => equalAggregate('2d3', 1, 2,
    checkInfo(t, 1, 0, paths.lazy, 0, 0),
    checkInfo(t, 3, 0, paths.lazy, 2, 0), 
    checkExtraInfo(t)
  ),
});

// EXERCISE 2A

function makeExWait(title) {
  return t => {
    const fails = ex2CheckExecs(t);
    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)];
    }
    const waitCommandIndex = t.commands.findIndex(x => x.startsWith("wait"));
    if (waitCommandIndex === -1) {
      return [0, 1, `CRITICAL (Inspect before marking) - no wait command sent to myshell?`];
    }
    const children = {};
    for (const line of t.trace) {
      switch (line.type) {
      case 'clone':
      case 'execve': {
        children[line.pid] = line;
        line.killed = false;
        line.exited = false;
        line.waited = false;
        line.waitcount = 0;
        break;
      }

      case 'wait': {
        if (!(line.waitpid in children)) {
          fails.push(`Wait called on wrong PID?`);
        } else if (children[line.waitpid].waited) {
          fails.push(`Waiting on command that has already exited and was waited on before`);
        } else {
          if (children[line.waitpid].exited) {
            children[line.waitpid].waited = true;
          }
          children[line.waitpid].waitcount += 1;
        }
        break;
      }

      case 'kill': {
        fails.push("Kill was used");
        break;
      }

      case 'sigchld': {
        const child = children[line.pid];
        if (child) {
          child.exited = true;
        }
        break;
      }

      case 'commandEnd': {
        if (line.index === waitCommandIndex) {
          for (const child of Object.values(children)) {
            if (!child.exited) {
              fails.push(`Wait returned before child ${child.path} PID ${child.pid} exited`);
            }
          }
        }
        break;
      }

      }
    }
    for (const child of Object.values(children)) {
      if (child.waitcount == 0) {
        fails.push(`Failed to wait for child ${child.pid}`);
      }
    }
    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)];
    }
    return [1, 1];
  };
}

Object.assign(testcases, {
  '2a1': makeExWait('2a1'),
  '2a2': makeExWait('2a2')
});

// EXERCISE 2B

function makeExTerminate(title) {
  return t => {
    const fails = ex2CheckExecs(t);
    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)];
    }
    const firstTerminateCommandIndex = t.commands.findIndex(x => x.startsWith("terminate"));
    if (firstTerminateCommandIndex === -1) {
      return [0, 1, `CRITICAL (Inspect before marking) - no terminate command sent to myshell?`];
    }
    const children = {};
    for (const line of t.trace) {
      switch (line.type) {
      case 'clone':
      case 'execve': {
        children[line.pid] = line;
        line.killed = false;
        line.exited = false;
        break;
      }

      case 'kill': {
        const child = children[line.pid];
        if (!child) {
          fails.push(`Wrong PID ${line.pid} killed`);
          break;
        }
        if (child.exited) {
          fails.push(`Killing exited child ${child.path} PID ${line.pid}`);
        }
        if (['SIGTERM', 'SIGKILL'].includes(line.signal)) {
          child.killed = true;
        }
        break;
      }

      case 'sigchld': {
        const child = children[line.pid];
        if (child) {
          child.exited = true;
        }
        break;
      }

      case 'pids': {
        if (line.pids.length > 0) {
          fails.push(`PIDs seen after terminate: ${line.pids.join(", ")}`);
        }
        break;
      }

      }
    }
    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)];
    }
    return [1, 1];
  };
}

Object.assign(testcases, {
  '2b1': makeExTerminate('2b1'),
  '2b2': makeExTerminate('2b2')
});

// EXERCISE 2C

function ex2CheckExec(t, ...argv) {
  const path = argv[0];
  const execs = t.filterExecs(path);
  if (argv[argv.length - 1] === "&") argv.pop();
  if (execs.length == 0) { return `Missing exec ${argv[0]} ${argv[1]}`; }
  for (const exec of execs) {
    if (exec.isMainProcess) {
      exec.seen = true;
      return "Parent process exec-ed";
    }
    const argvNoArgv0 = argv.slice(1);
    if (arrayEqual(exec.argv, argv)
      || arrayEqual(exec.argv.slice(1), argvNoArgv0)
      || arrayEqual(exec.argv.slice(1, argv.length - 1), argvNoArgv0)
      || arrayEqual(exec.argv.slice(0, argv.length - 1), argvNoArgv0)) {
      exec.seen = true;
      return;
    }
  }
  return `Missing exec ${argv[0]}`;
}

function ex2CheckExecs(t) {
  const execs = t.commands.filter(isRunProgramCommand).flatMap(c => c.split(" && ").map(exec => exec.split(/(<|>|2>)/)[0].trim().split(" ")));
  const fails = [];
  for (const exec of execs) {
    const failReason = ex2CheckExec(t, ...exec);
    if (failReason) {
      fails.push(failReason);
    }
  }
  if (t.getUnseenExecs().length > 0) {
    fails.push("Extraneous execs seen");
  }
  return fails;
}

function makeExChained(title, numExecs, numPasses) {
  return t => {
    const fails = [];

    let execFail = false;
    const argvs = t.commands[0].split(" && ").map(command => command.split(/(<|>|2>)/)[0].trim().split(" "));
    const execs = t.filterAllExecs();
    const execArgvs = execs.map(command => command.argv);
    if (execArgvs.length === numExecs) {
      for (let i = 0; i < numExecs; i++) {
        if (!arrayEqual(argvs[i], execArgvs[i])) {
          execFail = true;
          fails.push(`Expected ${argvs[i]}, got ${execArgvs[i]} in exec`);
        }
      }
    } else {
      execFail = true;
      fails.push(`Expected ${numExecs} execs, got ${execArgvs.length} execs`);
    }
    
    let waitFail = false;
    const execPids = execs.map(command => command.pid);
    const waitPids = t.filterAllWaits().map(command => command.waitpid);
    if (execPids.length === numExecs && waitPids.length === numExecs) {
      for (let i = 0; i < numExecs; i++) {
        if (waitPids[i] !== execPids[i]) {
          waitFail = true;
          fails.push(`Expected wait for pid ${execPids[i]}, got wait for pid ${waitPids[i]}`);
        }
      }
    } else {
      waitFail = true;
      fails.push(`Expected ${numExecs} waits, got ${waitPids.length} waits`);
    }

    let outputFail = false;
    const failMessages = t.filterFails();
    if (failMessages.length > 0) {
      outputFail = true;
      for (const message of failMessages) {
        fails.push(message);
      }
    }

    const passLines = t.filterPasses();
    if (passLines.length !== numPasses) {
      outputFail = true;
      fails.push(`Expected ${numPasses} passes, got ${passLines.length} passes`);
    }

    const failStr = joinComments(title, fails);
    if (outputFail && (execFail || waitFail)) {
      return [0, 1, failStr];
    } else if (outputFail || execFail || waitFail) {
      return [0.5, 1, failStr];
    } else {
      return [1, 1];
    }
  };
}

Object.assign(testcases, {
  '2c1': makeExChained('2c1', 2, 1),
  '2c2': makeExChained('2c2', 2, 1),
  '2c3': makeExChained('2c3', 9, 2),
  '2c4': makeExChained('2c4', 7, 2),
  '2c5': makeExChained('2c5', 5, 2)
});

// EXERCISE 2E

function makeExQuit(title) {
  return t => {
    const fails = ex2CheckExecs(t);
    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)];
    }

    const children = Object.fromEntries(t.trace.filter(t => ['execve', 'clone'].includes(t.type)).map(t => [t.pid, t]));
    for (const line of t.trace.filter(t => t.type === 'kill')) {
      const child = children[line.pid];
      if (!child) {
        fails.push(`Wrong PID ${line.pid} killed`);
      }
    }

    const lastPidCommand = t.trace.findLast(t => t.type === 'pids')
    if (!lastPidCommand) { return [0, 1, `CRITICAL (Inspect before marking) - cannot get pids at end of grading script?`]; }
    const lastPids = lastPidCommand.pids;
    for (const lastPid of lastPids) {
      if (!children.hasOwnProperty(lastPid)) { continue; }
      const child = children[lastPid];
      fails.push(`Child ${child.path} PID ${child.pid} remaining after shutdown`);
    }

    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)];
    }
    return [1, 1];
  };
}

Object.assign(testcases, {
  '2e1': makeExQuit('2e1'),
  '2e2': makeExQuit('2e2')
});

function makeEx3(title, numPasses) {
  return t => {
    let fails = ex2CheckExecs(t);
    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)];
    }
    fails = t.filterFails();
    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)]
    }
    const passes = t.filterPasses();
    if (passes.length != numPasses) {
      return [0, 1, `${title}: Expected ${numPasses} passes, got ${passes.length} passes`];
    }
    return [1, 1];
  };
}

// EXERCISE 3A

Object.assign(testcases, {
  '3a1': t => equalAggregate('3a1', 1, 2,
    checkInfo(t, 3, 0, paths.rio, 1, 0),
    checkInfo(t, 3, 1, paths.rio, 1, 0),
    checkExtraInfo(t)
  ),
  '3a2': makeEx3('3a2', 5),
  '3a3': makeEx3('3a3', 5)
});

// EXERCISE 3C

Object.assign(testcases, {
  '3b1': makeEx3('3b1', 2),
  '3b2': makeEx3('3b2', 2),
  '3b3': makeEx3('3b3', 2)
});

// EXERCISE 3C

Object.assign(testcases, {
  '3c1': makeEx3('3c1', 2)
});

// EXERCISE 3D

Object.assign(testcases, {
  '3d1': makeExChained('3d1', 9, 5),
  '3d2': makeExChained('3d2', 4, 4),
  '3d3': makeExChained('3d3', 7, 5)
});

// EXERCISE 4A

function makeEx4a(title) {
  return t => {
    const fails = [];

    // Find if fg sends SIGCONT to correct pid
    const childPid = t.findExec(paths.pw);
    if (childPid === undefined) {
      fails.push("exec for periodic write not found");
    } else {
      let sigcontFail = true;
      const killLines = t.filterKills('SIGCONT');
      for (const line of killLines) {
        if (Math.abs(line.pid) === childPid.pid) {
          sigcontFail = false;
          break;
        }
      }
      if (sigcontFail) {
        fails.push(`SIGCONT not sent to correct pid`);
      }
    }

    if (title === '4a1' || title === '4a3') {
      const allLines = t.trace;
      let beforeFg = true;
      let i = 0;
      let fgFail = true;
      for (const line of allLines) {
        if (line.raw.startsWith("periodic-write")) {
          if (i !== parseInt(line.raw.split("-")[2])) {
            fails.push("Out of sequence periodic write detected");
            break;
          }
          i++;
          if (!beforeFg) {
            fgFail = false;
          }
        } else if (line.type === "command" && line.raw.includes("fg")) {
          beforeFg = false;
        }
      }
      if (i === 0) {
        fails.push("No periodic writes detected");
      } else if (fgFail) {
        fails.push("fg does not work properly");
      }
    }

    if (title === '4a2') {
      const allLines = t.trace;
      let i = 0;
      for (const line of allLines) {
        if (line.raw.startsWith("periodic-write")) {
          if (i !== parseInt(line.raw.split("-")[2])) {
            fails.push("Out of sequence periodic write detected");
            break;
          }
          i++;
        }
      }
      if (i === 0) {
        fails.push("No periodic writes detected");
      }
      if (t.filterPasses().length !== 1) {
        fails.push("fg does not work properly");
      }
    }
    
    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)];
    }
    return [1, 1];
  };
}

Object.assign(testcases, {
  '4a1': makeEx4a('4a1'),
  '4a2': makeEx4a('4a2'),
  '4a3': makeEx4a('4a3')
});

// EXERCISE 4B

function makeEx4b(title, numPasses) {
  return t => {
    const fails = [];
    if (t.filterPasses().length !== numPasses) {
      fails.push("Children not sent SIGINT");
    }

    if (fails.length > 0) {
      return [0, 1, joinComments(title, fails)];
    }
    return [1, 1];
  };
}

Object.assign(testcases, {
  '4b1': makeEx4b('4b1', 1),
  '4b2': makeEx4b('4b2', 1),
  '4b3': makeEx4b('4b3', 1)
});
