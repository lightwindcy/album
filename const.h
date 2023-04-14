#ifndef CONST_H
#define CONST_H

enum TreeItemType{
    TreeItemPro =1, //项目的条目
    TreeItemDir,//项目的文件夹
    TreeItemPic,//项目的图片
};
enum PicBtnState {
    PicBtnStateNormal = 1,
    PicBtnStateHover = 2,
    PicBtnStatePress = 3,
    PicBtnState2Normal = 4,
    PicBtnState2Hover = 5,
    PicBtnState2Press = 6,
};

const int PROGRESS_WIDTH = 300;
const int PROGRESS_MAX = 300;
const int PREITEM_SIZE = 100;
const int PREICON_SIZE = 90;
const int MAX_SCREEN_WIDTH = 1900;
#endif // CONST_H
