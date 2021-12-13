#!/usr/bin/env node

import { gradeSubmission, print } from './grader_common.mjs';

async function main() {
  const bonus = process.argv[process.argv.length - 1] === "1";
  const [score, , comment] = await gradeSubmission(".", bonus);
  await print(`Score: ${score} / 7

${comment}
`);
}

main();
