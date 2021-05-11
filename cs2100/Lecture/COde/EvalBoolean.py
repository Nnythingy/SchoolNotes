def main():
  a,b,c = 4,-2,0

  x = (a > b or b > c and a == b)
  print("x =", x)

  y = ((a > b or b > c) and a == b)
  print("y =", y)
  _y = (a > b > c and a == b)
  print("_y =", _y)

  z = ((a > b) and not(b > c))
  print("z =", z)
  
  return 0

if __name__ == "__main__":
  main()
