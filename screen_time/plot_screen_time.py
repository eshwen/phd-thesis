import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def plot_aesthetics(df, ax):
    ax.set_xlabel('Date (MM-DD)')
    ax.set_ylabel('Screen time (hr)')
    ax.set_title('Screen time by program in the final month of my PhD', fontweight='bold')

    #enDash = u'\u2013'
    #ax.set_xticklabels(df['date'].str.replace('-', enDash), rotation=90)

    dates_to_show = np.where(df['day'].values == 'Monday', df['date'], '')
    ax.set_xticklabels(dates_to_show, rotation=90)

    ax.set_ylim([0., df['Total'].max() * 1.1])

    ax.spines["right"].set_visible(False)
    ax.spines["top"].set_visible(False)


df = pd.read_csv("screen_time_thesis.csv")
fig, ax = plt.subplots()

# Make line plot

line_colours = {
    'Total': 'navy',
    'Terminal': 'dodgerblue',
    'Firefox': 'cyan',
    'VS Code': 'mediumorchid',
    'Mattermost': 'darkorange',
    'Skype': 'lightslategray',
}

i = 0
for app, colour in line_colours.items():
    df[app] = pd.to_timedelta(df[app]).dt.total_seconds() / 3600.
    ax.plot(df['date'], df[app], color=colour, linewidth=2, label=app, zorder=-1 * i)  # zorder such that earlier lines are plotted on top of later ones
    i += 1

ax.legend(frameon=False, bbox_to_anchor=(1.05, 1.))
plot_aesthetics(df, ax)
plt.savefig('screen_time_line.pdf', bbox_inches='tight')

# Make stacked bar chart

ax.clear()

df['Other'] = df['Total'] - df['Terminal'] - df['Firefox'] - df['VS Code'] - df['Mattermost'] - df['Skype']
ax.bar(df['date'], df['Other'], color='lightslategray', label='Other')
ax.bar(df['date'], df['Skype'], color='cyan', label='Skype', bottom=df['Other'])
ax.bar(df['date'], df['Mattermost'], color='darkorange', label='Mattermost', bottom=df['Skype'] + df['Other'])
ax.bar(df['date'], df['VS Code'], color='mediumorchid', label='VS Code', bottom=df['Mattermost'] + df['Skype'] + df['Other'])
ax.bar(df['date'], df['Firefox'], color='dodgerblue', label='Firefox', bottom=df['VS Code'] + df['Mattermost'] + df['Skype'] + df['Other'])
ax.bar(df['date'], df['Terminal'], color='navy', label='Terminal', bottom=df['Firefox'] + df['VS Code'] + df['Mattermost'] + df['Skype'] + df['Other'])

plot_aesthetics(df, ax)
# Reverse legend order
handles, labels = ax.get_legend_handles_labels()
ax.legend(handles[::-1], labels[::-1], frameon=False, bbox_to_anchor=(1.05, 1.))

plt.savefig('screen_time_bar.pdf', bbox_inches='tight')
