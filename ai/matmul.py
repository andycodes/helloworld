import torch

arg1 = torch.tensor([[1, 2], [3, 4]])
arg2 = torch.tensor([[-1], [2]])
arg3 = torch.matmul(arg1, arg2)
print(arg3)

