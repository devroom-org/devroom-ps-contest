import re
from pathlib import Path
import shutil
import zipfile

syntax = re.compile(r"[#\[\\\]^{|}~]")
replace_map = {
    "#": "=",
    "[": "(",
    "\\": "/",
    "]": ")",
    "^": "'",
    "{": "<",
    "|": "!",
    "}": ">",
    "~": "-",
}

output_root = Path(".") / "output"
output_path_list = [*output_root.glob("*.c")]

input_root = Path(".") / "input"
if input_root.is_dir():
    shutil.rmtree(input_root)
input_root.mkdir()

def replace_to_trigraph(s):
    return syntax.sub(lambda match: "??"+replace_map[match.group()[0]], s)

filename_max_len = max(len(path.name) for path in output_path_list)
format = f"%{filename_max_len}s\t%5d\t%s"

for output_path in output_path_list:
    with output_path.open("r") as output_file:
        lines = output_file.readlines()
        print(format % (output_path.name, len(lines), 'Ok' if len(lines) < 5000 else '!!Err!!'))
        replaced = str(len(lines)) + "\n" + "".join(map(replace_to_trigraph, lines))
        input_path = output_path.parent.parent / "input" / output_path.name
        with input_path.open("w+") as input_file:
            input_file.write(replaced)

with zipfile.ZipFile(str(Path(".") / "testcases.zip"), 'w') as zip:
    id = 3
    id_map = {}
    for file in output_root.iterdir():
        curr_id = (
            0 if file.stem == 'sample1' else
            1 if file.stem == 'sample2' else
            2 if file.stem == 'sample3' else
            id
        )
        id_map[file.stem] = curr_id
        zip.write(
            str(file.resolve()),
            str("output/output%02d.txt" % curr_id),
            compress_type = zipfile.ZIP_DEFLATED
        )
        id += 1
    for file in input_root.iterdir():
        zip.write(
            str(file.resolve()),
            str("input/input%02d.txt" % id_map[file.stem]),
            compress_type = zipfile.ZIP_DEFLATED
        )
