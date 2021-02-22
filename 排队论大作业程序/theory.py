import math


def MMn(n, _lambda, _miu):
    rho = _lambda / _miu
    P0 = 1 / (
            sum([rho ** i / math.factorial(i) for i in range(0, n + 1)]) +
            rho ** (n + 1) / (math.factorial(n) * (n - rho))
    )
    Elq = (rho ** (n + 1) * P0) / (n * math.factorial(n) * (1 - rho / n) ** 2)
    return Elq
