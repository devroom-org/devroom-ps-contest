n, R = int(input()), int(input())
prev = [x + 1 for x in range(R)]
for _ in range(1, n):
    next = [1]
    for i in range(1, R):
        next.append((next[-1] + prev[i]) % 2147483659)
    prev = next
print(prev[-1])