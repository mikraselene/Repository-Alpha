/*

#id+(id*id)

E->TE'
T->FT'

Recursive-Descent Parsing
A()
    A -> Xi;
    for(i = 1:k)
        if(Xi in T)
            Xi()
        else if(Xi == a)
            Next()
        else
            Error()
end

LL(k)

S->aAd|aBe
A->c
B->b



NOT GOOD:
A->Aa
A=>+Aa

A->Aa|b
A   =>Aa
    =>Aaa
    =>Aa...a
    =>ba...a=ba*

A->Aa|b
>>
A->bA'
A'->aA'|#

left recursive >=> right recursive


S->Aa|b
A->Ac|Sd|#

S   =>Aa
    =>Sda
    =>...

A->Ac|Aad|bd|#

FOLLOW(A) = {a | S => *αAaβ; a in Vt; α, β in (Vt+Vn)*}
SELECT(A->)

FIRST(alpha)

*/