# Benternet 

## Voorwoord 

In dit project wordt het proces opgevlogd van het maken van een server service via een Zmq broker. 
Dit project wordt opgezet in functie van de lessesn die ik volg voor mijn bachlor opleiding. 

De service die ik gekozen heb om te maken is een Task Manager. 

## ZerroMQ broker 

ZerroMQ is een Open-scours univarsal messiging Library. Het maakt mogelijk om Netwerk sockets op te stellen 
waarmee message's kunnen verstuurt worden.Zeromq kan op veel mannieren gebruikt worden. wij zullen gebruik maken van
2 sockets: 1 om berichten te versturen (Push) en 1 om berichten te ontvangen (Sub). 


![image](https://user-images.githubusercontent.com/113888494/234383760-677335b2-9940-4442-b228-edc24ccf1729.png)


## communicatie 

de communicatie tussen client en Service werkt als volgend: 

Als 1ste moet de client zijn Subscriber socket ingesteld worden naar "?TaMa" dit 
zal er voor zorgen dat enkel de berichte van deze sevice zal aankomen. 

Vervolgens Stuurt de client via zijn Pusher socket een bericht met er voor "!TaMa"
dit omdat de service gesubscribed is op "!TaMa" wordt dit niet voor het bericht toegevoegd 
krijgt de server het bericht niet aan en kan er geen communicatie zijn.

De server stuurt hierna een bericht uit zodat de client weet dat hij ge connecteerd is. 

Hierna na kunnen er functie's opgevraagd worden. 

de logica die gevolgd word door de service is als volgend 

    "!TaMa<service.subservice"
    
Zoals hier boven uitgelegd is de "!TaMa"het sub gedeelde 
Alles na het "<" heeft betrekking tot de service die verwagt wordt
vb. 
    
    "!TaMa<GetTask1.datum" geeft de datum van de 1ste Task weer die is ingesteld. 
      

![image](https://user-images.githubusercontent.com/113888494/234489455-8dfafca0-7255-4737-a520-7599fed7d384.png)


## Functie's 


### Add Task 
    
    Het toevoegen van een task: Service Tag "ADDTask
        msg van de client:  "!TaMa<ADDTask.Tasknaam.TaskDatum"
        
        

### Delete Task 

 Het delete van een task: Service Tag "DelTask
        msg van de client:  "!TaMa<DelTask.Tasknaam"


### Change Task 

 Het veranderen van een task: Service Tag "ChangeTask
        msg van de client:  "!TaMa<ChangeTask.Tasknaam.Datum.(change)"
    




