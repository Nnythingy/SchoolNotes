## System Auditing Analysis

The folder `proj_tools` contains a set of scripts and tools useful for the system auditing final project.

### Simulated Attack

The simulated attack contains two users:

+ Attacker (`/home/attacker`)
  The attacker's goal is to steal the secret file (under `/home/student/secret/secret.txt`) from the victim.

+ Victim (`/home/student`)
  The victim user is the target of the attacker. This user runs the daemon *auditd* to collect system events (audit logs) during the attack. 

The whole attack chain is demonstrated as follows:

1) Server setup. The attacker runs an nginx web server and shares his programs to the public site `localhost:8080`.
2) Program downloads. The victim downloads a series of programs from the attacker's site `localhost:8080/programs/`.
3) Malware running. After downloading the programs (specifically, program1, program2, ..., program11), the victim runs those programs. 
However, one of the programs is malicious, and this malware copies the file `/home/student/secret/secret.txt` to the attacker's directory `/home/attacker/output.txt`. 

### System Auditing

We provide you with an interface script (`audit-ctl.sh`) to start/stop the system auditing daemon. 

To start the *auditd*: `sudo ./audit-ctl.sh start`. This command will do the following things:
1) Enable system *auditd* by using the default configurations.
2) Create an output folder `audit_out`.
3) Gather other system information (i.e., process information, network information, ...). The information will be under `audit_out/`.

To stop *auditd* and collect audit logs: `sudo ./audit-ctl.sh stop`. This command will gather audit logs to the `audit_out` folder.

Actually, `audit-ctl.sh` is just a top-level wrapper for other scripts under the [`audit`](./audit) directory.
You should read [`audit/config.sh`](./audit/config.sh) and [`audit/collect.sh`](./audit/collect.sh) for more details.

Specifically, you may need to configure your own *auditd* rules. To do so, please modify [`audit/config.sh`](./audit/config.sh).

### Get Started

1. Login the student **ssh environment**: `ssh student@localhost`. All the following commands should be run inside this ssh env.
2. Start *auditd* daemon for victim: `sudo ./audit-ctl.sh start`
3. Run the simulated attack: `./run-attack.sh`
4. Collect audit logs for victim: `sudo ./audit-ctl.sh stop`
5. **Analyze the audit logs and have fun :)**
