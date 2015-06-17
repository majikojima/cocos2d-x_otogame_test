//
//  Tja.h
//  testAtest
//
//  Created by kojimatomo on 2015/06/14.
//
//

#ifndef __testAtest__Tja__
#define __testAtest__Tja__

#include "cocos2d.h"

class Tja{
private:
    
    int loadHeader(std::string tjaFile);
    void loadCount(std::string tjaFile, int loadPoint);
    void loadNote(std::string tjaFile, int loadPoint);
    std::vector<std::string> split(const std::string& input, char delimiter);
public:
    Tja();
    virtual ~Tja();
    
    void loadTja();
    
    CC_SYNTHESIZE(int, _noteCount, NoteCount);  //音符数
    CC_SYNTHESIZE(int, _barCount, BarCount);    //小節数
    CC_SYNTHESIZE(std::vector<int>, _barNoteCount, BarNoteCount);   //一小節の音符数（0を含む）
    CC_SYNTHESIZE(std::string, _title, Title);  //曲名
    CC_SYNTHESIZE(int, _bpm, Bpm);              //テンポ
    CC_SYNTHESIZE(std::vector<int>, _noteTimes, NoteTimes);
};

#endif /* defined(__testAtest__Tja__) */
