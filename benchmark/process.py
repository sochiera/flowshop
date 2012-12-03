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
sys.stdout.write(str(len(numbers)))
for n in numbers:
  sys.stdout.write("\n")
  sys.stdout.write(str(n))
