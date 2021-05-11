# Conversion constant
KMS_PER_MILE = 1.609

# Get the distance in miles
miles = float(input("Enter distance in miles: "))

# Convert the distance to kilometres
kms = KMS_PER_MILE * miles

# Display the distance in kilometres
print("That equals", kms, "km.")
