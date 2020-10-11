/*

E   ->  TE'
E'  ->  +TE' | -TE' | eps
T   ->  FT'
T'  ->  *FT' | /FT' | eps
F   ->  (E) | id

            FIRST       FOLLOW
E           
E'
T           
T'          
F           

        +       -       *       /       (       )       id
E       ~       ~       ~       ~       TE'     TE'     ~
E'      TE'     TE'     ~       ~       ~       eps     ~
T       ~       ~       ~       ~       FT'     ~       FT'
T'      eps     eps     *FT'    *FT'    ~       eps     ~
F       ~       ~       ~       ~       (E)     ~       id


*/
