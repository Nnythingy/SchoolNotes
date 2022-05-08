"""
#week 5 qn 1
p = 31063972991647623853541756099888503395466070196029391328180599997166329227016215437036221421384569484371218404819404529600576963094112491538736267044367346892513413814988496087121518196884481391899748322244577040886269877380209045974186508471439583500101173636978059604066340145432197354850445463448141748111
g = 22288782973285336115971778582718628252618717468085700069078431476407890494996105251636393818504490718623724036797632257014857338899098805809605676118219744753310641567858243160714267899091792340811238560428533305396459740314078320542189472727536665769622923463362781601943927154372804562039969299058140689424
a = 21080441580136493638560155701910118663338297193677883154773600280391978297268702070636813020687426357856479065559597789350009145318155435829859872680409049387837882944108571449116787692269140839677681000189256583625570112801737949634435288474887507588568069737983927334375784745817764934250464864897370787753
#value that Alice sends Bob A
A = pow(g,a,p)
print(A)
# 20853104614706837805309671851702893497600890311640952479162285592296627269482326027726469663606084092172499154267913289079296385444934750986901652865152745099266157962458341748792244439707345661349638413351053001325577648271852952618107109391313428509582049559262911344548173230444425125056419853236672440012

# What is the value of the shared secret K
B = 13102568858566864698036573505653390827716848463015282982565627453758790170696478832369405465033469225804503281458163691651701235115240437289467880311304995769763250981713200060412657696848427846416759683538898804054094452697728816526913848432519387287574022501518132179984928760034512759581806741951833073282
k = pow(B,a,p)
print(k)
# 1373669142893166879959249847733443391195535349677323239358079374159248819095440769956253918622345875550275711850550381084512017116837287714449723232560340624962651182321470806225780977339487410795273765562408810581152774429708682943809377217695996652895743905946119948921049048245145869437640561493250305686
 """
""" 
#qn 2
What properties of the initialization vector (IV) must be maintained in order for CBC mode encryption to be secure? Assume AES if needed, choose all that apply.

- Value must bever be reused with the same key
- Value must not be predictable (ie be random)
"""
""" 
#qn 3
What properties of the nonce / initial counter value (aka initialization vector / IV) must be maintained in order for CTR mode encryption to be secure? Assume AES if needed, choose all that apply

- Value must never be reused with the same key n
# CTR IV should not be random since they contain less bits then the normal IV for CBC mode.
# This would mean that over the entire time of conversation, there is a possibility for repeating
# IV values used with the same key
 """
""" 
#qn 4
In another problem you'll be asked to modify an ElGamal ciphertext so that it has a predictable effect on the message upon decryption. What does this demonstrate about textbook ElGamal encryption?
(Hint: Recall that CPA stands for “chosen plaintext attack” and CCA for “chosen ciphertext attack”.
In CPA, the adversary gets to query arbitrary plaintexts to the Encrypt function and see the corresponding ciphertexts,
while being asked to break a challenge ciphertext (which can’t be the same as the queried ones). 
In CCA, the adversary can query the Decrypt function with arbitrary ciphertexts of its choice and see the decrypted plaintext,
in addition to querying the Encrypt function as in CPA, while being asked to break the challenge ciphertext.)

- ElGamal provides CPA security but not CCA security
 """
""" 
#qn 5
Why is Diffie-Hellman Key Exchange (as described in the previous section) secure against an eavesdropper (Eve) who can see all values sent?

- Multiplying numbers takes polynomial time, but finding the discrete logarithm of a number takes nearly exponential time in the number of bits
 """
""" 
#qn 6
# this is because that e*d = 1 mod phiN
# thus d = 1 mod phiN / e == d = e^-1 mod phiN

phiN = 6584678423672333093337797027720661473449990414131293991599890733744221590421379145494728996345295938440589701316517457679675180765632388636430767839749870210768883790987874146084603059456086327459726062557131500467431394747700935475466455918752231175470992509933778319351432610345143861202305667727389010964716854410264226104858840156655530353209663905065200389874967166111236659518823541910715979923465088960174853855109612431060110879153043534582875192412723911161968143261799985353964384830897107578941584746032084850275920628571639178107052481657594273970769124308561417853077148905237978222550485834083905782880
N = 6584678423672333093337797027720661473449990414131293991599890733744221590421379145494728996345295938440589701316517457679675180765632388636430767839749870210768883790987874146084603059456086327459726062557131500467431394747700935475466455918752231175470992509933778319351432610345143861202305667727389010964893875060423854875738496737437779412853004752747783282243283160232032566166952959073347429392182415964338990951443676807842971344760129361738832536273181795670939925484559850772797480757552210292975776680245355726521159461233982899853821938345124064403288978211753105202589807191378685061001934555353533317139
e = 1248983483192323910097544533077500662624785661103393487061755605475835419831605267566528375268064622812223649178704270164350654529135926971235323093364935274938832136631149508862297330145890539207215235803815406112665112953468304532387401819864112085141850259779988352809621557030717381980237886359951195390384060383573255812577283388699741088010715379850929920756916213752255269101540314136176772717483337360716361262709195745628826571266202840635185725843546507185169461782403592967930807831976519570257431921671256173932514320463790067866626742665066471544876453932986120968142060862971385277707314746832459263229
d = pow(e,-1,phiN)
print(d)
# 3441488463136561860803968134950315447610532042868686300583693490141945528936804593181556288169477074428365004470211417295608520532525161123073060941532964290734389386708451524533674184266187307526947715683768918160297698635069481823584693403867077388478796364779400134793434609791550849492782820368035602154186123514055637635455960941911891376280749097416778644826868757893098602545863345350831656606561542008341273875632494440753252310100668338176205637049439620884547163002821919950243096187222489849519889327010365642446625450491980972457059493508031073897277200681007130225713326631022077494811822727484553814389

c = int("0cf6a80a21f91996b482e3449f0eb72befa18d23858e7ea9e9bedbbbbf7e72f380f21a04452ce8455a351aa9ab6336370f13da1c3ee1b019196d99898521510867019dca3df3599e3cfac16f47240fb9d037a64198f6ecfa3f25e9174e63dc53540e5499c4771398e7905a9f6cf2488e38f3da7936a09c4c20fab428f817920f2c4ad109f9b9f59b141d0eba159e6ad0772a764ca1f64f2a4f164948ee15256a4edb91a51bcb329da84f88453d3dd40ea3d806609c96d5e40c7c2a8707e2fea3bed3e6dee2c1d436ad66e77f5d4a5991b27e663c630a64116e7e6e753124fcc30822097b5e2b11b8041c999c4adffd550b63397a3a0d0b9d2ddf4f0b579fc8cf", 16)
m = pow(c,d,N)
# 0x43727970746f677261706879206973207479706963616c6c792062797061737365642c206e6f742070656e65747261746564
bytes_array = bytes.fromhex(hex(m)[2:])
ascii_str = bytes_array.decode()
print(ascii_str)

# Cryptography is typically bypassed, not penetrated
# print (e*d%phiN) #checking
 """
""" 
#qn 7
# The idea behind this is that ElGamal is that not CCA secured. Modifying the ciphertext by multiplying to the t (which is message multiply by Bob public key)
# This way, after everything is being decrypted, it will still remain with modified 'm'

# given: p, g, B
# k is randomly chosen
# r = pow(g, k, p)
# t = pow(m*B, k, p)

t = 14645938109506385234767212532378052408507866868381592903296136578492288335864428658740298604915677274995542432194162148549739051840001972792156243519434692680959248309053254892689457002481046635097584204955182474073222712107626248439050745049704067010323376434508504975298147976507142709551629949620413714105878986
r = 63215478154945646917647873059947329496101308345658422456918703742104863884633153042268015621911097691375977404871132199899361247148993069415235776465298941359093875885848686672952972200281218440668416433981013480402316717831922833877774616563343079893909424902023872819227817425695619131764703684009034239099
p = 130107307752432694718805710085351634004559013242599968753103776158453316545086339865659142635426214989372065965382855971038023506470364847975820576349938930122998899501850927249534277755917898924711332999900545229741101121254006057779486965425469498008773841403493931068523504279701500522533335705798649468939
tm = pow(t*10, 1, p)
print(tm)
 """
""" 
#qn8
# When p and q are too close together for RSA parameters, especially when |p-q| < 2*N**1/4
# Then fermat factorization would be able to to find p and q from N
# The below method is the basic method, of finding all values of 'a' hoping that b^2

import gmpy2
N = 313902753513750806483270958858324724745964174178394825715464704114718429770848255614687929933860805512548821521230539752737915587185428856885548466469996094154393752850872214193649894965772356189047126798111509155440750848536603471880555547633744051363805121503918408483085256187111455395473241058594342889733251890035943761300648672491989897543536318330864647145569930142867836559850234672808501611056039976198091428991316458041978532207979968578873240858626313624326776761231117887164145349414778769371267385273756285506014135350888669326353349176075432302456159664565387193008973411330347582317833464318466665309
a = gmpy2.isqrt(N)
b2 = gmpy2.square(a) - N

while not gmpy2.is_square(b2):
    a += 1
    b2 = gmpy2.square(a) - N

p = a + gmpy2.isqrt(b2)
q = a - gmpy2.isqrt(b2)
print("p=", p, "\nq=", q, "\n", p-q)
print(q if p > q else p)
 """