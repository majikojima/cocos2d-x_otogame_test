//
//  Tja.cpp
//  testAtest
//
//  Created by kojimatomo on 2015/06/14.
//
//

#include "Tja.h"

USING_NS_CC;

const int BPM_BASE = 120;

Tja::Tja()
:_noteCount(0)
,_barCount(0)
//,_barNoteCount(NULL)
,_bpm(120)
//,_title(NULL)
//,_noteTimes(NULL)
{
    
}

Tja::~Tja(){
    
}

void Tja::loadTja(){
    auto tjaFile = FileUtils::getInstance()->getStringFromFile("test.tja");
    log("Tja %s", tjaFile.c_str());
    
    int loadPoint = loadHeader(tjaFile);   //ヘッダー読み込み
    log("loadPoint = %d", loadPoint);
    
    loadCount(tjaFile, loadPoint);
    
    loadNote(tjaFile, loadPoint);

}

int Tja::loadHeader(std::string tjaFile){
    auto lines = split(tjaFile, '\n');
    for(int i=0; i<lines.size(); i++){
        if(lines[i].find("TITLE:") != std::string::npos){
            this->setTitle(lines[i].substr(strlen("TITLE:")));
            log("TITLE = %s", getTitle().c_str());
        }
        else if(lines[i].find("BPM:") != std::string::npos){
            this->setBpm(std::stoi(lines[i].substr(strlen("BPM:"))));
            log("BPM = %d", getBpm());
        }
        else if(lines[i].find("#START") != std::string::npos){
            return (int)tjaFile.find("#START") + strlen("#START");
        }
    }
    return -1;
}

void Tja::loadCount(std::string tjaFile, int loadPoint){
    int barNoteCount = 0;   //一小節の音符数
    for(int i=loadPoint+1; i<tjaFile.size(); i++){
//        log("tjaFile[%d] = %c", i, tjaFile[i]);
        switch(tjaFile[i]){
            case '0':
            case 'e':
                barNoteCount++;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
                _noteCount++;
                barNoteCount++;
                break;
            case ',':
                _barCount++;
                _barNoteCount.push_back(barNoteCount);
                barNoteCount = 0;
                break;
            default:
                break;
        }
    }
//    log("%d,%d", _noteCount, _barCount);
//    for(std::vector<int>::iterator it = _barNoteCount.begin(); it != _barNoteCount.end(); it++){
//        log("%d", *it);
//    }
}

void Tja::loadNote(std::string tjaFile, int loadPoint){
    std::vector<int> noteTimes;
    std::vector<int> barNoteCounts = getBarNoteCount();
    int barCount = 0;
    int barNoteCount = 0;   //一小節の音符数
    
    for(int i=loadPoint+1; i<tjaFile.size(); i++){
//        log("tjaFile[%d] = %c", i, tjaFile[i]);
        switch(tjaFile[i]){
            case '0':
            case 'e':
                barNoteCount++;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
                noteTimes.push_back((BPM_BASE / barNoteCounts.at(barCount) * barNoteCount + barCount * BPM_BASE) * BPM_BASE / getBpm());
                
                barNoteCount++;
                break;
            case ',':
                barNoteCount = 0;
                barCount++;
                break;
            default:
                break;
        }
    }
    for(std::vector<int>::iterator it = noteTimes.begin(); it != noteTimes.end(); it++){
        log("noteTime = %d", *it);
    }
    
    setNoteTimes(noteTimes);
}

std::vector<std::string> Tja::split(const std::string& input, char delimiter){
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;
    while (std::getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}