n, k = map(int, input().split())
s1 = input().strip()
s2 = input().strip()

if s1[0] != s2[0]:
    print("NO")
    exit()

ops = [0] * 105
used = [False] * 105
for i in range(n - 1, -1, -1):
    found = False
    for j in range(i, -1, -1):
        if s2[i] == s1[j] and not used[j]:
            ops[i] = j
            # 将所有大于j的位置都标记为已占用
            for t in range(j + 1, n):
                used[t] = True
            found = True
            break
    if not found:
        print("NO")
        exit()

max_ops = 0
for i in range(n):
    max_ops = max(max_ops, i - ops[i])
if k >= max_ops:
    print("YES")
else:
    print("NO")
