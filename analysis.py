import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv('ytest23.csv')

bdf = df.loc[df['source'] == 'B']
gdf = df.loc[df['source'] == 'G']

df = df.drop(index=df.index[0])
print(bdf['value'].mean())

plt.plot(bdf['time'], bdf['value'], '-o', label="B", color='blue')
plt.plot(gdf['time'], gdf['value'], '-o', label="G", color='green')
plt.legend()
plt.show()

#print(rratio, irratio, R)
