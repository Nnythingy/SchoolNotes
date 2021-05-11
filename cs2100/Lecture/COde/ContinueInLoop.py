def main():
  # Without 'continue'
  print("Without 'continue':")
  for i in range(1,6):
    print(i)
    print("Ya")

  # With 'continue'
  print("With 'continue':")
  for i in range(1,6):
    print(i)
    if i == 3:
      continue
    print("Ya")
  
  # With 'continue' in a nested loop
  print("With 'continue' in a nested loop:")
  for i in range(1,4):
    for j in range(1,6):
      print(i, ",", j)
      if j == 3:
        continue
      print("Ya")

  return 0

if __name__ == "__main__":
  main()
