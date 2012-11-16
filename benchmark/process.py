import re
import json
import sys

# filter stdin
lines = []
for line in sys.stdin.readlines():
  if not re.match('^number', line) and not re.match('^processing', line):
    lines.append(line)

text = ''.join(lines)
numbers = map(int, text.split())

# read problem description
i = 0
problems = []
while i != len(numbers):
  problem = {}
  jobs = numbers[i]; i += 1
  machines = numbers[i]; i += 2
  problem['jobs'] = jobs
  problem['machines'] = machines
  problem['upper_bound'] = numbers[i]; i += 1 
  problem['lower_bound'] = numbers[i]; i += 1 
  times = []
  for machine in range(machines):
    for job in range(jobs):
      times.append(numbers[i])
      i += 1
  problem['times'] = times
  problems.append(problem)

sys.stdout.write(json.dumps(problems))
