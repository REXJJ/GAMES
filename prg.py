import pygame, sys, os
from pygame.locals import *
FPS=30
a=4
b=4
xcons=500
ycons=400
y1=0
y2=0
z=8
z1=50
l=100
x=xcons/2
y=ycons/2
sy=0
sx=0
BLACK = (0,0,0)
RED=(255,0,0)
BLUE=(0,0,255)
bar1_score, bar2_score = 0,0

def main():
  global DISPLAYSURF, fpsClock,y1,y2,z,l,x,y,z1
  pygame.init()
  font = pygame.font.SysFont("calibri",40)
  fpsClock=pygame.time.Clock()
  DISPLAYSURF = pygame.display.set_mode((500, 400), 0, 32)
  pygame.display.set_caption('PRING PRONG')
  ny=0
  my=0
  flag=False
  flagy=False
  while True:
    DISPLAYSURF.fill((255,255,255))
    pygame.draw.rect(DISPLAYSURF, RED, (0, 0, xcons, 5))
    pygame.draw.rect(DISPLAYSURF, RED, (0, ycons-5, xcons, 5))
    pygame.draw.rect(DISPLAYSURF, RED, (0, y1, 10, l))
    pygame.draw.rect(DISPLAYSURF, RED, (xcons-10, y2, 10, l))

    if os.path.isfile('./NEW.txt'):
          file=open("./NEW.txt","r")
          char =file.read()
          if char=='a':
            if y1<ycons-l:
              y1=y1+z1
          elif char=='q':
            if y1>0:
              y1=y1-z1
        
          os.remove('./NEW.txt')    
    
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()          
        
        if event.type==KEYDOWN:
              if event.key==K_l:
                 my=z
                 flagy=True
              elif event.key==K_p:
                 my=-z
                 flagy=False
        elif event.type==KEYUP:
              if event.key==K_l:
                 my=0
              elif event.key==K_p:
                 my=0
    if y1>=ycons-l and flag:
        ny=0
    if y1==0 and not flag:
        ny=0
    if y2>=ycons-l and flagy:
        my=0
    if y2==0 and not flagy:
        my=0
         
    #if y2<ycons-l or y2==0:
     # my=0
    
    y2=y2+my

    if x >=xcons/2:
        if not y2 == y + 7.5:
            if y2 < y + 7.5:
              if y2<ycons-l:
                 y2 += z
            if  y2 > y - 42.5:
              if y2>0:
                y2 -= z
    else:
            y2 == y + 7.5
    
    
    score1 = font.render(str(bar1_score), True,(0,255,255))
    score2 = font.render(str(bar2_score), True,(0,255,255))
    middle_line = pygame.draw.aaline(DISPLAYSURF,(255,0,255),(xcons/2,0),(xcons/2,ycons))
    #screen.blit(bar1,(bar1_x,bar1_y))
    #screen.blit(bar2,(bar2_x,bar2_y))
    #screen.blit(circle,(circle_x,circle_y))
    DISPLAYSURF.blit(score1,(xcons/4,ycons/2))
    DISPLAYSURF.blit(score2,((xcons*3)/4,ycons/2))
    game()
    pygame.display.update()      
    fpsClock.tick(FPS)
    
def game():
    global x,y,sy,sx,y1,y2,bar1_score,bar2_score
    yb1=y1+l
    yb2=y2+l
    if sx==0:
        x=x-b
    elif sx==1:
        x=x+b
    if sy==0:
        y=y-a
    elif sy==1:
        y=y+a
    if y<10:
        sy=1
    elif y>ycons-10:
        sy=0
    if x<=20 and (y>=y1 and y<=yb1):
        sx=1
    elif x>=xcons-20 and (y>=y2 and y<=yb2):
        sx=0
    if x<10:
       x=xcons/2
       y=ycons/2
       bar2_score+=1
    if x>xcons-15:
       x=xcons/2
       y=ycons/2
       bar1_score+=1
    pygame.draw.circle(DISPLAYSURF, BLUE, (x, y), 10, 0)
if __name__ == '__main__':
    main()
