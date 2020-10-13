def simulate_aging(Rs, k: int) -> None:
    """Simulate aging."""
    Vs = [0] * len(Rs[0])
    for t, R in enumerate(Rs):
        for i in range(len(Vs)):
            Vs[i] = R[i] << k - 1 | Vs[i] >> 1
        print('%02d  |  %s  |  [%s]' % (t, R, ', '.join([format(V, '0%db' % k) for V in Vs])))

Rs = [[1,0,1,0,1,1], [1,1,0,0,1,0], [1,1,0,1,0,1], [1,0,0,0,1,0], [0,1,1,0,0,0]]
k = 8
simulate_aging(Rs, k)
