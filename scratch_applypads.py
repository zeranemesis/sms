import json, re, os

pads = json.load(open('scratch_pads.json'))
todo = []
for d, lst in pads.items():
    d = int(d)
    if d >= 0:
        continue  # target frame smaller: padding can't help
    for unit, fn in lst:
        todo.append((unit, fn, -d))  # bytes to add
print(f"negative-delta pads (bytes to add): {len(todo)}")

def srcpath(unit):
    rel = unit.split('/', 1)[1]
    return os.path.join('src', rel + '.cpp')

# group by file
byfile = {}
for unit, fn, n in todo:
    byfile.setdefault(srcpath(unit), []).append((unit, fn, n))

applied, skipped = [], []
for p, items in byfile.items():
    if not os.path.exists(p):
        skipped.extend((u, f, 'no file') for u, f, _ in items)
        continue
    text = open(p, encoding='utf-8', errors='replace').read()
    ok = True
    for unit, fn, n in items:
        base = fn.split('__')[0]
        pat = re.compile(r'(\b[\w:<>~ ]*?\b' + re.escape(base) + r'\s*\([^;{]*\)\s*(?:const\s*)?)\{')
        ms = [m for m in pat.finditer(text) if not re.search(r';\s*$', m.group(1))]
        if not ms:
            skipped.append((unit, fn, 'no def'))
            ok = False
            continue
        m = ms[0]
        ins_at = m.end()
        pad = (f"\n\t// Frame-padding: target frame is {n} bytes larger (MWCC stack-padding quirk).\n"
               f"\tchar pad[{n}];\n\t(void)pad;")
        text = text[:ins_at] + pad + text[ins_at:]
        applied.append((unit, fn, n))
    if ok:
        open(p, 'w', encoding='utf-8', newline='').write(text)

print(f"applied: {len(applied)}")
for a in applied:
    print("  ", a[2], a[0].split('/', 1)[1], '::', a[1].split('__')[0])
print(f"skipped: {len(skipped)}")
for s in skipped:
    print("  ", s)
