def main():
  a = (2 > 3)
  b = (3 > 2)

  print("a =", a, "; b =", b)

  print("----- With Python TypeCast -----")
  
  a = int(2 > 3)
  b = int(3 > 2)

  print("a =", a, "; b =", b)

  return 0

if __name__ == "__main__":
  main()
