import sys

print("Size of 'smaller int' (in bytes):", sys.getsizeof(1))
print("Size of 'larger int' (in bytes):", sys.getsizeof(2**64))
print("Size of 'even larger int' (in bytes):", sys.getsizeof(2**128))
print("Size of 'float/double' (in bytes):", sys.getsizeof(5.2**64))
print("Size of 'char' (in bytes):", sys.getsizeof('A'))
