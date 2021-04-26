#include <stdio.h>
#include <SDL.h>

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL; // ����
    SDL_Renderer *render = NULL;// ��Ⱦ��
    SDL_Texture *texture = NULL; // ����
    SDL_Event event; // �����¼�
    int quit = 0; // �Ƿ��˳�
    int win_w = 640; // ���ڿ��
    int win_h = 480; // ���ڸ߶�
    SDL_Rect rect; // ���Ƶľ���
    rect.w = 40;
    rect.h = 40;

    // ��ʼ��
    SDL_Init(SDL_INIT_VIDEO);

    // �������ڣ������ֱ��Ǵ��ڵı��⣬x,y,w,h�����һ��������һЩflag(SDL_WINDOW_SHOWN��ʾ��������ʾ����)
    window = SDL_CreateWindow("���ڱ���",300,300,win_w,win_h,SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("��������ʧ��\n");
        goto __EXIT;
    }

    // ������Ⱦ
    // ������Ⱦ��
    render = SDL_CreateRenderer(window,-1,0);// ������Ⱦ��
    if (!render)
    {
        printf("����Ⱦ����ʧ��\n");
        goto __DESTROY;
    }
    // SDL_SetRenderDrawColor(render,255,0,0,255); // ���ô�����ɫ�����漸�������ֱ���RGBA
    // SDL_RenderClear(render); // ��մ���
    // SDL_RenderPresent(render); // ������չʾ����

    // ���������ڶ���������ָ�����ظ�ʽ��������YUV��RGB����3��������ָ���������ͣ�������stream(��)��target(һ������)��
    texture = SDL_CreateTexture(render,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,win_w,win_h);
    if (!texture)
    {
        printf("������ʧ��!\n");
        goto __DESTROY;
    }


    // SDL_Delay(10000);
    // �����˳��¼�
    do
    {
        // SDL_WaitEvent(&event);
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
        {
            quit = 1;
        }else{
            printf("�¼�����:%d\n", event.type);
        }

    // ������þ���λ��
    rect.x = rand()%600;
    rect.y = rand()%440;

    // �����������Ⱦ
    SDL_SetRenderTarget(render,texture); // �ı���ȾĿ��Ϊ����
    SDL_SetRenderDrawColor(render,255,255,255,255); // ����������ɫ(��ɫΪRGBA)
    SDL_RenderClear(render); // �����Ⱦ��
    // ���ƾ��β������������ɫ
    SDL_RenderDrawRect(render,&rect); // ���ƾ���
    SDL_SetRenderDrawColor(render,rand()%256,rand()%256,rand()%256,255); // �������������ɫ
    SDL_RenderFillRect(render,&rect); // ���
    // �ָ���Ĭ����ȾĿ��
    SDL_SetRenderTarget(render,NULL);
    // ��Ŀ��������Կ�
    SDL_RenderCopy(render,texture,NULL,NULL);
    SDL_RenderPresent(render); // �Կ�������������ʾ
    } while (!quit);

__DESTROY:
    if (window) // ����window
    {
        SDL_DestroyWindow(window);
    }
    if (render) // ������Ⱦ��
    {
        SDL_DestroyRenderer(render);
    }
    if (texture) // ��������
    {
        SDL_DestroyTexture(texture);
    }


__EXIT:
    // �˳�
    SDL_Quit();
    return 0;
}
