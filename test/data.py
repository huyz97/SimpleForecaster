import pandas as pd
import numpy as np

def gen_test():
    symbols = ["aaa","aab","abb","zzz","123","cbc","tst","hhh"]

    timestamp = 52924702
    data = []
    for i in range(100000):
        symbol = np.random.choice(symbols)
        timestamp += np.random.randint(1,10)
        quantity = np.random.randint(1,100)
        price = np.random.randint(1,100)
        data.append([timestamp,symbol,quantity,price])
    df = pd.DataFrame(data=data,columns=["timestamp","symbol","quantity","price"])

    df.to_csv("./test_larege.csv",index=None,header=None)

def read_test():
    df = pd.read_csv("./test-large.csv",header=None,names=["timestamp","symbol","quantity","price"])
    print(df.groupby("symbol").max(),df.groupby("symbol").sum())

gen_test()
# read_test()