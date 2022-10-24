import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os

dirname = os.path.dirname(__file__)+'/../'
file_path = dirname+'../out_data/dataset_reports/KITTI/[BRIGHTNESS]barchart_data.dat'
df = pd.read_csv(file_path)


# sub_df = df[['name','count', '1sigma', '2sigma', '3sigma']]
sub_df = df[['name', '1sigma', '2sigma', '3sigma']]

# plot grouped bar chart
ax = sub_df.plot(x='name',
        kind='bar',
        stacked=False,
        width = 0.9,
        # title='Grouped Bar Graph with dataframe',
        rot=0,
        xlabel='Sequences',
        ylabel='# images')
ax.legend(['|\u03B2|> \u03C3', '|\u03B2|> 2\u03C3', '|\u03B2|> 3\u03C3'])
ax.grid(b=True, which='major', color='lightgray', linestyle='--')


# for p in ax.patches:
#     ax.annotate(str(p.get_height()), (p.get_x() , p.get_height() * 1.01), rotation=90)

plt.show()