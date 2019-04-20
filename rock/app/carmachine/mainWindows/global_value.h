#ifndef GLOBAL_VALUE_H
#define GLOBAL_VALUE_H

#include <QStandardPaths>
#include "mainwindow.h"

extern mainWindow *mainwid;
extern rightStackedWidgets0 *wifiWid;

#ifdef DEVICE_EVB
const int font_size = 30;
const int font_size_big = 35;
// top part
const QString return_resource_str = ":/image/main/return_big.png";
const int return_icon_width = 212;
const int return_icon_height = 70;
const int top_icon_size = 60;
#else
const int font_size = 13;
const int font_size_big = 16;
// top part
const QString return_resource_str = ":/image/main/return.png";
const int return_icon_width = 115;
const int return_icon_height = 40;
const int top_icon_size = 40;
#endif



// music
//const QString MUSIC_SEARCH_PATH = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).append("/mnt");
//const QString str_add_song= "添加音乐";
//const QString str_clear_list= "清空列表";
//const QString str_song_list= "歌曲列表";
//const QString str_song_playing= "正在播放中";
//const QString str_playmode_list= "列表循环";
//const QString str_playmode_random= "随机播放";
//const QString str_playmode_single= "单曲循环";
//const QString str_origin_move_songname = "请先指定曲目";
//// video
//const QString VIDEO_SEARCH_PATH = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).append("/mnt");
//const QString str_listheader_local_video = "本地视频";
//const QString str_listheader_net_video = "网络视频";
//const QString str_video_playing = "播放中";
//const QString str_videoName_default = "视频播放器";
//const QString str_videoTime_minite= "分钟";
//// setting
//const QString str_net_manager= "网络管理";
//const QString str_bt_manager= "蓝牙管理";
//const QString str_common_setting= "通用设置";
//const QString str_system_setting= "系统设置";
//const QString str_open_wifi= "打开WLAN";
//const QString str_wifi_adapter= "网卡适配器";
//// gallery
//const QString str_top_title = "图片预览";
//const QString str_gallery_empty_tip1= "本机媒体中的所有图片";
//const QString str_gallery_empty_tip2= "保存在您设备文件夹中的照片会显示在此处.";
//const QString str_button_edit_image= "编辑图片";
//const QString str_button_refresh_image= "刷新";
//const QString str_button_edit_image_cancel= "取消";
//const QString str_button_delete_image= "删除";
//const QString str_image_and_preview= "★ 图片与预览";
//const QString str_imge_have_seleted1= "当前已选中 ";
//const QString str_imge_have_seleted2= " 项";
//const QString str_question_Tip= "警告";
//const QString str_question_delete_image= "删除图片？";


//const QString str_image_information= "图片信息";
//const QString str_confirm= "确定";
//const QString str_image_name= "名称";
//const QString str_image_pattern= "格式";
//const QString str_image_resolution= "图片尺寸";
//const QString str_image_location= "位置";
//const QString str_image_size= "文件大小";
//const QString str_image_create_time= "创建时间";
//const QString str_resolution_tip = "像素(宽×高)";
//const QString str_button_delete= "删除";
//const QString str_button_cancel= "取消";


// music
const QString MUSIC_SEARCH_PATH = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).append("/mnt");
const QString str_add_song= "Add music";
const QString str_clear_list= "Clear list";
const QString str_song_list= "musicPlay";
const QString str_song_playing= "Playing";
const QString str_playmode_list= "List";
const QString str_playmode_random= "Random";
const QString str_playmode_single= "Single";
const QString str_origin_move_songname = "Please first select one music";
// video
const QString VIDEO_SEARCH_PATH = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).append("/mnt");
const QString str_listheader_local_video = "Local Video";
const QString str_listheader_net_video = "Net Video";
const QString str_video_playing = "Playing";
const QString str_videoName_default = "videoPlayer";
const QString str_videoTime_minite= "min";
// setting
const QString str_net_manager= "Wlan";
const QString str_bt_manager= "BlueTooth";
const QString str_common_setting= "General";
const QString str_system_setting= "System";
const QString str_open_wifi= "WLAN";
const QString str_wifi_adapter= "adapter";
// gallery
const QString str_top_title = "imageGallery";
const QString str_gallery_empty_tip1= "All in the family";
const QString str_gallery_empty_tip2= "Take a picture & Photo saved on this device appear here.";
const QString str_button_edit_image= "EditMode";
const QString str_button_refresh_image= "Refresh";
const QString str_button_edit_image_cancel= "Cancel";
const QString str_button_delete_image= "Delete";
const QString str_image_and_preview= "★ Image and Preview";
const QString str_imge_have_seleted1= "Current has   ";
const QString str_imge_have_seleted2= "   images seleted";

const QString str_image_information= "Image Infomation";
const QString str_confirm= "Confirm";
const QString str_image_name= "Name";
const QString str_image_pattern= "Pattern";
const QString str_image_resolution= "Resolution";
const QString str_image_location= "Location";
const QString str_image_size= "Size";
const QString str_image_create_time= "CreateTime";
const QString str_resolution_tip = "(width×height)";
const QString str_question_Tip= "warm";
const QString str_question_delete_image= "Delete images？";
const QString str_button_delete= "Delete";
const QString str_button_cancel= "Cancel";

#endif
