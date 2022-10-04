import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def line_equatuation(weights):
        lines = []
        #assumes weights = [x1*weight,x2*cost,bias]
        for i in range(len(weights)):
            m = -(weights[i][0]/weights[i][1])
            #y intercept
            b = -(weights[i][2]/weights[i][1])
            lines.append([m,b])

        return lines