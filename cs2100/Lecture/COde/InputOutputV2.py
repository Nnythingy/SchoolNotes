def main():
  user_input = input("What are your age and CAP? ")
  age,cap = user_input.split(" ")
  age,cap = int(age),float(cap)
  print("You are", age, "years old, and your CAP is", cap)

  return 0

if __name__ == "__main__":
  main()
