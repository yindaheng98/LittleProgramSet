import numpy as np
feature_size = 3
sequence_lengeh = 10

K = np.zeros((1, feature_size))
Q = np.zeros((1, feature_size))
V = np.zeros((1, feature_size))
QK = np.matmul(Q, K.T)
QKV = np.matmul(QK, V)
for i in range(0, sequence_lengeh):
    k = np.random.random((1, feature_size))
    q = np.random.random((1, feature_size))
    v = np.random.random((1, feature_size))

    # 将新来的向量k和q单独计算后拼接
    Qk = np.matmul(Q, k.T)  # 新的QxK结果中最后一行
    qK = np.matmul(q, K.T)  # 新的QxK结果中最后一列
    qk = np.matmul(q, k.T)  # 新的QxK结果中最后一行中的最后一列上的元素
    qK_qk = np.concatenate((qK, qk), axis=1)  # 新的QxK结果中完整最后一行
    QK_Qk = np.concatenate((QK, Qk), axis=1)  # 新的QxK结果中少了完整最后一行
    V = np.concatenate((V, v), axis=0)
    qK_qkV = np.matmul(qK_qk, V)  # QxKxV结果中的最后一行
    QKv = np.matmul(Qk, v)  # QxKxV结果中相对于上一步的增量
    QKV = np.concatenate((QKV + QKv, qK_qkV), axis=0)
    QK = np.concatenate((QK_Qk, qK_qk), axis=0)

    K = np.concatenate((K, k), axis=0)
    Q = np.concatenate((Q, q), axis=0)
    print("Feature Size:", "K:", K.shape, "Q:", Q.shape, "V:", V.shape)

print("Feature Size:", "Q x K.T:", Q.shape, "x", K.T.shape)
S = np.matmul(Q, K.T)
print("Feature Size:", "(Q x K.T) x V:", S.shape, "x", V.shape)
Z = np.matmul(S, V)
print("Feature Size:", "(Q x K.T) x V:", Z.shape)
print("(Q x K.T) x V:")
print(Z)
print("迭代式(Q x K.T) x V:")
print(QKV)
print("差距:", (Z - QKV).sum())
