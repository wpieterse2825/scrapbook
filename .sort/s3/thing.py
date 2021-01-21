final_file = open("final.txt", "r")
final_content = final_file.readlines()
final_file.close()

content_lengths = {}

final_content_unique = set(final_content)
for item in final_content_unique:
    content_lengths[item] = len(item)

smallest_items = 128
largest_item = 0
average = 0
count = 0

for (key, value) in content_lengths.items():
    if value > largest_item:
        largest_item = value

    if value < smallest_items:
        smallest_items = value

    average += value
    count += 1

final_average = average / count

other_average = average + (count * 2)

final_average += 2
smallest_items += 2
largest_item += 2

print("Total    : %s" % count)
print("Length   : %s" % other_average)
print("Average  : %s" % final_average)
print("Smallest : %s" % smallest_items)
print("Largest  : %s" % largest_item)
