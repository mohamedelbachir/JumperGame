#include"TextureManager.h"
#include<map>
#include<iostream>
TextureManager* TextureManager::s_pInstance=NULL;

TextureManager::TextureManager(){}

TextureManager::~TextureManager(){
    cleanUp();
}

void TextureManager::cleanUp(){
    std::map<std::string,SDL_Texture *>::iterator it;
    for(it=m_textureMap.begin();it!=m_textureMap.end();it++){
        SDL_DestroyTexture(it->second);
        delete it->second;
    }
    std::cout<<"Texture Nettoyer..."<<std::endl;
    m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id){
    SDL_DestroyTexture(m_textureMap[id]);
    delete m_textureMap[id];
    m_textureMap.erase(id);
}

bool TextureManager::load(std::string filepath, std::string id, SDL_Renderer* pRenderer){

    SDL_Texture *pTexture;
    pTexture=IMG_LoadTexture(pRenderer,filepath.c_str());
    if(pTexture==NULL){
        return false;
    }
    m_textureMap[id]=pTexture;

    return true;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height,SDL_Rect src,SDL_Renderer* pRenderer, SDL_RendererFlip flip){

    SDL_Rect dstRect={0};


    dstRect.x=x;
    dstRect.y=y;

    dstRect.w=width;
    dstRect.h=height;

    SDL_RenderCopyEx(pRenderer,m_textureMap[id],&src,&dstRect,0,0,flip);

}

/*void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip){

    SDL_Rect srcRect={0};
    SDL_Rect dstRect={0};

    srcRect.x=width*currentFrame;
    srcRect.y=height*(currentRow-1);

    dstRect.x=x;
    dstRect.y=y;

    srcRect.w=dstRect.w=width;
    srcRect.h=dstRect.h=height;

    SDL_Point center={0};

    center.x=width/2;
    center.y=height/2;

    SDL_RenderCopyEx(pRenderer,m_textureMap[id],&srcRect,&dstRect,0,&center,flip);

}
*/
