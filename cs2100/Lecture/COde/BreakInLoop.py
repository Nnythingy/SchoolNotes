def main():
  # Without 'break'
  print("Without 'break':")
  for i in range(1,6):
    print(i)
    print("Ya")

  # With 'break'
  print("With 'break':")
  for i in range(1,6):
    print(i)
    if i == 3:
      break
    print("Ya")

  # With 'break' in a nested loop
  print("With 'break' in a nested loop:")
  for i in range(1,4):
    for j in range(1,6):
      print(i, ",", j)
      if j == 3:
        break
      print("Ya")

  return 0

if __name__ == "__main__":
  main()
