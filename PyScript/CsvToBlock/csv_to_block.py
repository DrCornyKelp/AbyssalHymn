import pandas as pd
import numpy as np

class Block:
    def __init__(self, x, y, w, h, id, valid = True):
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.id = id
        self.valid = valid

    def to_string(self):
        b_string = f"0,{self.x},{self.y},{self.w},{self.h}"
        for r in self.id:
            for c in r:
                b_string += f",{c}"

        return b_string + "\n"

# MERGE COLUMN
def mergeCol(block1, block2):

    empty = Block(0,0,0,0,0,False)

    # Different X
    if block1.x != block2.x: return empty
    # Different Width
    if block1.w != block2.w: return empty
    # Same Y
    if block1.y == block2.y: return empty
    # Invalid Merge Position
    if block1.y > block2.y and block1.y - block2.y != block2.h:
        return empty
    if block1.y < block2.y and block2.y - block1.y != block1.h:
        return empty
    
    # Create new block
    newX = block1.x
    newY = min(block1.y, block2.y)
    newW = block1.w
    newH = block1.h + block2.h
    newId = None
    if block1.y > block2.y:
        newId = block1.id + block2.id
    if block1.y < block2.y:
        newId = block2.id + block1.id

    return Block(newX, newY, newW, newH, newId)

# MERGE COLUMN
def mergeRow(block1, block2):

    empty = Block(0,0,0,0,0,False)

    # Different Y
    if block1.y != block2.y: return empty
    # Different Height
    if block1.h != block2.h: return empty
    # Same X
    if block1.x == block2.x: return empty
    # Invalid Merge Position
    if block1.x > block2.x and block1.x - block2.x != block2.w:
        return empty
    if block1.x < block2.x and block2.x - block1.x != block1.w:
        return empty

    # Create new block
    newX = min(block1.x, block2.x)
    newY = block1.y
    newW = block1.w + block2.w
    newH = block1.h
    newId = []
    if block1.x > block2.x:
        for r in range(newH):
            newId += [block2.id[r] + block1.id[r]]
    if block1.x < block2.x:
        for r in range(newH):
            newId += [block1.id[r] + block2.id[r]]

    return Block(newX, newY, newW, newH, newId)

# Initialize stuff
BlockMainVec = []
real_path = [0, 35, 36, 10, 37]
df = pd.read_csv('PyScript/CsvToBlock/ldtk_map.csv')
map_index = np.array(df, int)
map_index = np.flip(map_index, axis=0)
row, col = map_index.shape

# Initialize single block
for c in range(col):
    for r in range(row):
        if (map_index[r,c] != 0):
            BlockMainVec.append(
                Block(c,r,1,1,[[real_path[map_index[r,c]]]])
            )

# SORTING FUNCTION
def custom_sort_y(block):
    return (block.y, block.x)

# MERGE INTO COLUMN
BlockVecMergeCol = [BlockMainVec[0]]
for block in BlockMainVec[1:]:
    checkblock = mergeCol(block, BlockVecMergeCol[-1])

    if checkblock.valid:
        BlockVecMergeCol.pop()
        BlockVecMergeCol.append(checkblock)
    else:
        BlockVecMergeCol.append(block)

# MERGE INTO ROW
## Sort the col vec first
BlockVecMergeCol = sorted(BlockVecMergeCol, key=custom_sort_y)
BlockVecMergeRow = [BlockVecMergeCol[0]]
for block in BlockVecMergeCol[1:]:
    checkblock = mergeRow(block, BlockVecMergeRow[-1])

    if checkblock.valid:
        BlockVecMergeRow.pop()
        BlockVecMergeRow.append(checkblock)
    else:
        BlockVecMergeRow.append(block)

map_data_string = ""
for block in BlockVecMergeRow:
    map_data_string += block.to_string()

with open('PyScript/CsvToBlock/new_map.csv', 'w') as file:
    file.write(map_data_string)