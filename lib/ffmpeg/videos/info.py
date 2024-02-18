try:
    import os
    import sys
    import time
    import traceback
    import ffmpeg
    import xlwt
# 使用pip.main()方法进行依赖库的安装（例举几个常用的库）
except ImportError:
    import pip
    pip.main(["install", "--user", "ffmpeg-python==0.2.0", "xlwt==1.3.0"])
    import os
    import sys
    import time
    import traceback
    import ffmpeg
    import xlwt

# 需要安装的库
# libs = ["ffmpeg-python==0.2.0", "xlwt==1.3.0"]

# # 循环遍历安装
# for lib in libs:
#     os.system("pip install " + lib)
SCRIPT_NAME = os.path.basename(__file__)
COMMANDS = {
    '-h': '111',
    '-i': '222'
}


def main():
    # 获取当前文件所在绝对目录路径
    dir_path = os.path.abspath('.')
    # 准备日志文件
    f_fail = open('error.log', 'a', encoding='utf-8')  # 追加模式

    # 指令
    action_name = 'info'
    # args
    arg_len = len(sys.argv)

    if arg_len >= 2:
        action_name = sys.argv[1]
        print('start action', action_name, ", args =", sys.argv)
    else:
        print('start action', action_name)

    if action_name == '-h':
        print_help()
    elif action_name == '':
        trans(dir_path, f_fail)
    elif action_name == 'info':
        info(dir_path, f_fail)

    f_fail.close()


def print_help():
    print('usage:')
    print('command:')
    for item in COMMANDS:
        print('\t', item, '', COMMANDS[item])
    print('arguments:')
    print('\tpython {0}                   分析目录中的视频文件'.format(SCRIPT_NAME))
    print('\tpython {0} {1}                转换目录中的视频文件'.format(SCRIPT_NAME, '-i'))


def info(dir_path, f_fail):
    print('当前路径为          ---', dir_path, '开始分析文件')
    # 获取所有文件
    file_list = get_all_file(dir_path)
    print("文件读取完毕        --- 3秒后开始分析视频 ---")
    time.sleep(3)
    # 解析文件
    dict_all = get_all_dict(file_list, f_fail)
    save_xlwt(dict_all)
    print("文件分析完毕")


def trans(dir_path, f_fail):
    print('当前路径为          ---', dir_path, '开始转换文件')
    # 获取所有文件
    # file_list = get_all_file(dir_path)
    print("文件读取完毕        --- 3秒后开始转换视频 ---")
    time.sleep(3)


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


def get_source_info_ffmpeg(source_name):
    return_value = []
    try:
        info = ffmpeg.probe(source_name)
        # print(info)
        # print("---------------------------------")
        vs = next(c for c in info['streams'] if c['codec_type'] == 'video')
        # 文件大小
        filesize = info['format']['size']
        # 文件格式
        format_name = info['format']['format_name']
        # 码率
        bit_rate = info['format']['bit_rate']
        # 视频编码格式 hevc
        codec_name = vs['codec_name']
        # 视频编码格式 H.265 
        codec_long_name = vs['codec_long_name']
        duration = float(vs['duration'])
        # 帧率
        fps = vs['r_frame_rate']
        # 分辨率
        width = vs['width']
        height = vs['height']
        # 颜色 yuv
        pix_fmt = vs['pix_fmt'] 
        print("filesize:{} \nformat_name:{} \nduration:{} \ncodec_name:{} \ncodec_long_name:{} \nfps:{} \nbit_rate:{} \npix_fmt:{} \nwidth:{} \nheight:{}".format(
            filesize, format_name, duration, codec_name, codec_long_name, fps, bit_rate, pix_fmt, width, height))
        # [文件大小, 总时长, 视频格式, 帧率, 码率, 分辨率w, 分辨率h, ]
        return_value = [filesize, duration, codec_long_name, fps, bit_rate, width, height]
    except (OSError, TypeError, ValueError, KeyError, SyntaxError) as e:
        print("init_source:{} error. {}\n".format(source_name, str(e)))
        return_value = []
    return return_value


def trans_video_ffmpeg(source_name):
    ffmpeg.input(source_name, {
        
    })


def trans_videos_ffmpeg(file_list, output, f_fail):
    for file in file_list:
        filename = os.path.split(file)[1]
        print('\n\n', '开始提取此文件信息  ---', filename)
        time.sleep(0.1)
        try:
            # info_list1 = get_dict_data(get_media_info(file))
            # 获取文件详情
            
            print('文件信息提取成功    ---')
        except Exception as e:
            print('文件信息提取失败    ---', e)
            f_fail.write('\r\n' + filename + '\r\n')
            f_fail.write(traceback.format_exc() + '\r\n')


def get_all_dict(file_list, f_fail):
    dict_all = {}
    for file in file_list:
        filename = os.path.split(file)[1]
        print('开始提取此文件信息  ---', filename)
        time.sleep(0.1)
        # [文件大小, 总时长, 视频格式, 帧率, 码率, 分辨率w, 分辨率h, ]
        dict_all['文件名'] = ["文件大小", "总时长", "视频格式", "帧率", "码率", "帧宽", "帧高"]
        try:
            # info_list1 = get_dict_data(get_media_info(file))
            # 获取文件详情
            info_list = get_source_info_ffmpeg(file)
            # ['13726665', '23/1', 2507776.0, 'mov,mp4,m4a,3gp,3g2,mj2', 720, 400]
            print('info_list', info_list)
            dict_all[filename] = info_list
            print('文件信息提取成功    ---')
        except Exception as e:
            print('文件信息提取失败    ---', e)
            f_fail.write('\r\n' + filename + '\r\n')
            f_fail.write(traceback.format_exc() + '\r\n')
    return dict_all


def save_xlwt(dict_all):
    # 创建一个excel表存放文件路径信息，第一列是目录，第二列是文件名
    wb = xlwt.Workbook()
    sh = wb.add_sheet('元数据')

    row_count = 0
    for item in dict_all:
        sh.write(row_count, 0, item)
        index = 0
        for tmp in dict_all[item]:
            index += 1
            sh.write(row_count, index, tmp)
        row_count += 1
    #
    wb.save("元数据统计.xls")


# python info.py arg1 arg2 arg3...
# arg1 action: 
if __name__ == '__main__':
    main()
