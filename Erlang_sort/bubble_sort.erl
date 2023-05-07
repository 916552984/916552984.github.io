%%%-------------------------------------------------------------------
%%% @author 15622
%%% @copyright (C) 2023, <COMPANY>
%%% @doc
%%%
%%% @end
%%% Created : 04. 5月 2023 22:59
%%%-------------------------------------------------------------------
-module(demo1).
-author("15622").

%% API
-export([bubble_sort/3,my_sort/4,t_sort/1]).

%%主要排序函数，使用冒泡算法，两两比较
bubble_sort(L,O,1)->
  SL=L++O;
bubble_sort(L,O,S)->
  [A,B|C]=L,
  if
     A>B->
       NL=[A|C],
       TL=O++[B];
    true ->
       NL=[B|C],
       TL=O++[A]
  end,
  bubble_sort(NL,TL,S-1).

%%辅助函数，循环排序
my_sort(Rl,List,Z,0)->
    io:format("~w~n",[Rl]);
my_sort(Rl,List,Z,X)->
  [K|J]=bubble_sort(List,Z,X),
  KK=[K]++Rl,
  my_sort(KK,J,Z,X-1).

%%辅助函数，直接输入列表即可自动排序
t_sort(List)->
  Size=length(List),
  my_sort([],List,[],Size).









