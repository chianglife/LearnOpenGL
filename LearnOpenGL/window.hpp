//
//  window.hpp
//  LearnOpenGL
//
//  Created by Chiang on 2022/7/27.
//

#ifndef window_hpp
#define window_hpp

#include <stdio.h>
//定义两个函数指针
typedef void(*pipline)();
typedef void(*draw)();
int initWindow(pipline pipline, draw draw);
#endif /* window_hpp */

