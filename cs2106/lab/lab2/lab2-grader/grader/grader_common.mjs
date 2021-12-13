#!/usr/bin/env node

import { promisify, inspect } from 'util';
import * as path from 'path';

import { Trace } from './common.mjs';
import testcases from './testcases.mjs';

export const print = promisify(process.stdout.write.bind(process.stdout));

function exerciseAggregate(title, toMax, numberOfLines, results) {
  const lines = results.filter(([tc]) => tc.startsWith(title));
  if (lines.length !== numberOfLines) {
    throw new Error("Wrong number of testcases in?");
  }

  const perLine = toMax / numberOfLines;
  let total = 0;
  const comments = [];
  for (const [, [score, max, comment]] of lines) {
    if (typeof score !== 'number' || typeof max !== 'number') {
      throw new Error(`Non-numeric score/max? ${inspect([score, max])}`);
    }
    total += score * perLine / max;
    if (comment) {
      comments.push(comment);
    }
  }
  total = Math.max(Math.min(total, toMax), 0);
  return { title, score: total, max: toMax, comment:
`Ex ${title}: ${round2dp(total)} / ${toMax}
${comments.map(l => `- ${l}`).join("\n")}
`.trim() };
}

function aggregateEx2(...ex2Aggregates) {
  const totalScore = ex2Aggregates.map(aggregate => aggregate.score).reduce((a, b) => a + b, 0);
  return { 
    title: 'Ex 2',
    score: totalScore,
    max: 2,
    comment: 
`Ex 2: ${round2dp(totalScore)} / 2
${ex2Aggregates.map(aggregate => aggregate.comment.split('\n').slice(1).join("\n").trim()).join("\n").trim()}
`.trim()
  }
}

export function round2dp(v) {
  return Math.round(v * 100) / 100;
}

export async function gradeSubmission(dirPath, bonus) {
  const results = await Promise.all(Object.entries(testcases).map(async ([tc, fn]) => {
    if ((bonus && !tc.startsWith("4")) || (!bonus && tc.startsWith("4"))) {
      return ['', ''];
    }
    const trace = await Trace.fromFile(path.join(dirPath, `myshell.${tc}.trace`));
    const result = fn(trace);

    const additionalComments = [];

    const exitSignal = trace.signal || trace.exitcodeSignal;
    if (exitSignal) {
      additionalComments.push(`Note: killed by ${exitSignal}`);
    }

    if (trace.readCommandFail) {
      additionalComments.push(`Note: runner failed to read line: "${trace.readCommandFail}" - possible bad FD manipulation`);
    }

    if (additionalComments.length > 0) {
      if (result[2]) {
        result[2] += "; ";
      } else {
        result[2] = `${tc}: `;
      }
      result[2] += additionalComments.join("; ");
    }
    return [tc, result];
  }).filter(r => r !== null));
  let aggregates = null;
  if (!bonus) {
    aggregates = [
      exerciseAggregate("1", 3, 10, results),
      aggregateEx2(
        exerciseAggregate("2a", 0.3, 2, results),
        exerciseAggregate("2b", 0.3, 2, results),
        exerciseAggregate("2c", 0.6, 5, results),
        exerciseAggregate("2d", 0.5, 3, results),
        exerciseAggregate("2e", 0.3, 2, results),
      ),
      exerciseAggregate("3", 2, 10, results),
    ];
  } else {
    aggregates = [
      exerciseAggregate("4", 2, 6, results)
    ];
  }
  const total = round2dp(aggregates.reduce((x, y) => x + y.score, 0));
  return [total, "", aggregates.map(a => a.comment).join("\n").trim(), ...aggregates.map(a => round2dp(a.score))];
}
