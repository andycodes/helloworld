import torch

# 检查是否有可用的GPU
if torch.cuda.is_available():
    print("There is a GPU available.")
else:
    print("There is no GPU available.")

