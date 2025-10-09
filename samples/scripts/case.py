try:
    import os
    import sys
    import time
    import xlrd
    import json
# 使用pip.main()方法进行依赖库的安装（例举几个常用的库）
except ImportError:
    import pip
    pip.main(["install", "--user", "ffmpeg-python==0.2.0",
             "xlwt==1.3.0", "xlrd==2.0.1"])
    import os
    import sys
    import time
    import xlrd


SCRIPT_NAME = os.path.basename(__file__)


def main():
    # 获取当前文件所在绝对目录路径
    dir_path = os.path.abspath('.')
    # 准备日志文件
    f_fail = open('error.log', 'a', encoding='utf-8')  # 追加模式

    # args
    arg_len = len(sys.argv)

    if arg_len >= 2:
        xls_name = sys.argv[1]
        print('start action', xls_name, ", args =", sys.argv)
        if verify(dir_path, xls_name, f_fail):
            list = analyze_xlwt(dir_path, xls_name, f_fail)
            data = {
                "status": "0",
                "msg": "",
                "serverTime": "2023.07.14",
                "data": {
                    "has_next_page": "1",
                    "list": list,
                }
            }
            save_json(data)
        else:
            print('file verify error')
    else:
        print('start error')

    f_fail.close()


def verify(dir_path, file, f_fail):
    print('当前路径为          ---', dir_path, '开始分析文件')
    verify = True
    filepath = os.path.join(dir_path, file)
    if os.path.isdir(filepath):
        print('不能分析文件夹信息--' % (filepath))
        verify = False
    else:
        if not file.endswith('xls'):
            print("文件不是 xls 表格")
            verify = True
    return verify


def get_all_file(dir_path):
    list = []
    for file in os.listdir(dir_path):
        # print(file)
        filepath = os.path.join(dir_path, file)
        # print(filepath)
        if os.path.isdir(filepath):
            print('遇到子目录---%s---此版本暂不提取子目录视频信息--' % (filepath))
            time.sleep(2)
            # get_all_file(filepath)
        else:
            if not file.endswith('exe'):
                list.append(filepath)
    return list


def analyze_xlwt(dir_path, file, f_fail):
    # 创建一个excel表存放文件路径信息，第一列是目录，第二列是文件名
    filepath = os.path.join(dir_path, file)
    excel = xlrd.open_workbook(filepath)  # 打开excel文件
    sheet = excel.sheet_by_index(0)  # 获取工作薄

    # rows: list = sheet.row_values(0)  # 获取第一行的表头内容
    # index = rows.index('username')  # 获取age列所在的列数: 1，也可以换成"password"
    # listindes = sheet.col_values(index)  # 获取age列的所有内容

    return_value = []
    # 遍历该列所有的内容
    rows: list = sheet.row_values(0)
    for row_index in range(1, sheet.nrows):
        item = {
            "from": "yl_tj",
            "video_type": 1,
        }
        item480 = {
            "from": "yl_tj",
            "video_type": 1,
        }
        item360 = {
            "from": "yl_tj",
            "video_type": 1,
        }
        title480 = sheet.cell_value(row_index, rows.index('width*height,480P'))
        title360 = sheet.cell_value(row_index, rows.index('width*height,360P'))
        for col_index in range(sheet.ncols):
            row_key = sheet.cell_value(0, col_index)
            row_val = sheet.cell_value(row_index, col_index)
            width = sheet.cell_value(row_index, rows.index('width'))
            height = sheet.cell_value(row_index, rows.index('height'))
            
            print(
                '信息-- index:{} row_key:{}, row_val:{}'.format(row_index, row_key, row_val))
            if row_key == 'id':
                item['id'] = row_val
                item480['id'] = row_val
                item360['id'] = row_val
            elif row_key == 'h265':
                item['video_url'] = row_val.strip()
                item['title'] = formatTitle('测试 {} {}*{} 原视频'.format(row_index, width, height))
            elif row_key == '480P':
                item480['video_url'] = row_val.strip()
                item480['title'] = formatTitle('测试 {} {} 档位2 480P'.format(row_index, title480))
            elif row_key == '360P':
                item360['video_url'] = row_val.strip()
                item360['title'] = formatTitle('测试 {} {} 档位1 360P'.format(row_index, title360))
        return_value.append(item)
        return_value.append(item480)
        # return_value.append(item360)
    print('list', return_value)
    return return_value


def formatTitle(self: str):
    return self.replace('\n', ' ').replace('\t', ' ').strip()
    

def save_json(dict_all):
    # json_str = json.dumps(dict_all)
    with open("format_json.json", 'w', encoding='utf-8') as write_f:
        json.dump(dict_all, write_f, ensure_ascii=False)


# python info.py arg1 arg2 arg3...
# arg1 action:
if __name__ == '__main__':
    main()
