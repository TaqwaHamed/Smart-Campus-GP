from datetime import datetime
import os
import csv

def markAttendance(name): 
    header = ['Name', 'Time']
    now = datetime.now()
    datestring = now.strftime('%y-%m-%d')
    csv_filename = datestring+'.csv'
    if not os.path.exists(csv_filename):
        with open(csv_filename, 'w', encoding='UTF8') as f:
            writer = csv.writer(f)
            # write the header
            writer.writerow(header)
            f.close()

    with open(csv_filename,'r+') as f:
        myDataList = f.readlines()
        nameList = []
        for line in myDataList:
            entry = line.split(',')
            nameList.append(entry[0])
        if name not in nameList:
            now = datetime.now()
            dtString = now.strftime('%H:%M:%S')
            print("not found")
            f.writelines(f'\n{name},{dtString}')

