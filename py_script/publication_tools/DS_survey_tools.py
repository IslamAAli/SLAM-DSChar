import gspread as gs
import os

json_token = os.path.dirname(__file__)+'/dssurvey-5836227159b5.json'
sa = gs.service_account(filename=json_token)
sheet = sa.open('Survey On SLAM/Odometry Dataset')
worksheet = sheet.worksheet('MainData')

sheet_list = worksheet.get('B3:BE66')

for list_data in sheet_list:
    print(list_data)