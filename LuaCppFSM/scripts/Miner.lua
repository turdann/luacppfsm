-- Datos globales lo ven todos.
-- the amount of gold a miner must have before he feels he can go home
ComfortLevel       = 5
-- the amount of nuggets a miner can carry
MaxNuggets         = 3
-- above this value a miner is thirsty
ThirstLevel        = 5
-- above this value a miner is sleepy
TirednessThreshold = 5

-- Ubicaciones
shack = 1
goldmine = 2
bank = 3
saloon = 4

class 'Miner' (Actor)
function Miner:__init(name)
	super(name)
	print("[Miner] init is called from ".._VERSION)
	self.m_Location=shack	-- Datos locales de la clase Miner
	self.m_iFatigue=0		-- solo se ven dentro de la clase Miner.
	self.m_iGoldCarried=0
	self.m_iMoneyInBank=0
	self.m_iThirst=0
	self:GetFSM():SetCurrentState(GoHomeAndSleepTilRested) -- Ponemos el estado inicial
end
function Miner:__finalize()
	print("[Miner] finalize is called from ".._VERSION)
end

function Miner:GoldCarried()
	return self.m_iGoldCarried
end
function Miner:SetGoldCarried(val)
	self.m_iGoldCarried = val
end
function Miner:AddToGoldCarried(val)
	self.m_iGoldCarried = self.m_iGoldCarried + val
  	if self.m_iGoldCarried < 0 then
  		self.m_iGoldCarried = 0
  	end
end
function Miner:DecreaseFatigue()
	self.m_iFatigue = self.m_iFatigue -1
end
function Miner:IncreaseFatigue()
	self.m_iFatigue = self.m_iFatigue +1
end
function Miner:Location()
	return self.m_Location
end
function Miner:ChangeLocation(val)
	self.m_Location = val
end
function Miner:PocketsFull()
	return self.m_iGoldCarried >= MaxNuggets
end
function Miner:Thirsty()
	return self.m_iThirst >= ThirstLevel
end
function Miner:AddToWealth(val)
	self.m_iMoneyInBank = self.m_iMoneyInBank + val
	if self.m_iMoneyInBank < 0 then
		self.m_iMoneyInBank = 0
	end
end
function Miner:Wealth()
	return self.m_iMoneyInBank
end
function Miner:Fatigued()
	return self.m_iFatigue > TirednessThreshold
end
-------------------------------------------------------------------------------
-- create the EnterMineAndDigForNugget state
-------------------------------------------------------------------------------
EnterMineAndDigForNugget={}
EnterMineAndDigForNugget["Enter"]=function(pMiner)
  	-- if the miner is not already located at the goldmine, he must
  	-- change location to the gold mine
	if pMiner:Location() ~= goldmine then
    	print( "Miner"..pMiner:ID()..": Walkin' to the goldmine")
    	pMiner:ChangeLocation(goldmine)
    end
     
end
EnterMineAndDigForNugget["Execute"]=function(pMiner)
	-- Now the miner is at the goldmine he digs for gold until he
  	-- is carrying in excess of MaxNuggets. If he gets thirsty during
  	-- his digging he packs up work for a while and changes state to
  	-- gp to the saloon for a whiskey.
  	pMiner:AddToGoldCarried(1)
	pMiner:IncreaseFatigue()
	print("Miner"..pMiner:ID()..": Pickin' up a nugget")
	-- if enough gold mined, go and put it in the bank
 	if pMiner:PocketsFull() then
  		pMiner:GetFSM():ChangeState(VisitBankAndDepositGold)
	end
	if pMiner:Thirsty() then
  		pMiner:GetFSM():ChangeState(QuenchThirst)
	end
end
EnterMineAndDigForNugget["Exit"]=function(pMiner)
	  print("Miner"..pMiner:ID()..": Ah'm leavin' the goldmine with mah pockets full o' sweet gold")
end
EnterMineAndDigForNugget["OnMessage"]=function(pMiner,msg)
	-- send msg to global message handler
  	return false;
end
-------------------------------------------------------------------------------
-- create the VisitBankAndDepositGold state
-------------------------------------------------------------------------------
VisitBankAndDepositGold={}
VisitBankAndDepositGold["Enter"]=function(pMiner)
  	-- on entry the miner makes sure he is located at the bank
	if pMiner:Location() ~= bank then
		print("Miner"..pMiner:ID()..": Goin' to the bank. Yes siree")
		pMiner:ChangeLocation(bank)
	end
end
VisitBankAndDepositGold["Execute"]=function(pMiner)
	-- deposit the gold
  	pMiner:AddToWealth(pMiner:GoldCarried())
    pMiner:SetGoldCarried(0);
	print("Miner"..pMiner:ID()..": Depositing gold. Total savings now: "..pMiner:Wealth())
	-- wealthy enough to have a well earned rest?
  	if pMiner:Wealth() >= ComfortLevel then
  		print("Miner"..pMiner:ID()..": WooHoo! Rich enough for now. Back home to mah li'lle lady")
		pMiner:GetFSM():ChangeState(GoHomeAndSleepTilRested)      
  	else
  		-- otherwise get more gold
    	pMiner:GetFSM():ChangeState(EnterMineAndDigForNugget)
	end
end
VisitBankAndDepositGold["Exit"]=function(pMiner)
	print("Miner"..pMiner:ID()..": Leavin' the bank")
end
VisitBankAndDepositGold["OnMessage"]=function(pMiner, msg)
	-- send msg to global message handler
  	return false;
end
-------------------------------------------------------------------------------
-- create the GoHomeAndSleepTilRested state
-------------------------------------------------------------------------------
GoHomeAndSleepTilRested={}
GoHomeAndSleepTilRested["Enter"]=function(pMiner)
	if pMiner:Location() ~= shack then
    	print("Miner"..pMiner:ID()..": Walkin' home")
	    pMiner:ChangeLocation(shack); 
	    -- let the wife know I'm home
    	Dispatch:DispatchMsg(SEND_MSG_IMMEDIATELY,	--time delay
        	     		     pMiner:ID(),	        --ID of sender
            	             ent_Elsa,            	--ID of recipient
                	         Msg_HiHoneyImHome, 	--the message
                    	     NO_ADDITIONAL_INFO)    
  	end
end
GoHomeAndSleepTilRested["Execute"]=function(pMiner)
	-- if miner is not fatigued start to dig for nuggets again.
  	if not(pMiner:Fatigued()) then
		print("Miner"..pMiner:ID()..": All mah fatigue has drained away. Time to find more gold!")
     	pMiner:GetFSM():ChangeState(EnterMineAndDigForNugget)
  	else 
	    --sleep
    	pMiner:DecreaseFatigue()
	    print("Miner"..pMiner:ID()..": ZZZZ... ")
  	end
end
GoHomeAndSleepTilRested["Exit"]=function(pMiner)
end
GoHomeAndSleepTilRested["OnMessage"]=function(pMiner, msg)
	--   SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE)
	if msg.Msg == Msg_StewReady then
		print("Message handled by Miner"..pMiner:ID().." at time: "..Clock:GetCurrentTime())
		--SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);
	    print("Miner"..pMiner:ID()..": Okay Hun, ahm a comin'!")
	    pMiner:GetFSM():ChangeState(EatStew)
	    return true;
	end
	return false -- send message to global message handler
end
-------------------------------------------------------------------------------
-- create the QuenchThirst state
-------------------------------------------------------------------------------
QuenchThirst={}
QuenchThirst["Enter"]=function(pMiner)
	if pMiner:Location() ~= saloon then
	    pMiner:ChangeLocation(saloon)
    	print("Miner"..pMiner:ID()..": Boy, ah sure is thusty! Walking to the saloon")
    end
end
QuenchThirst["Execute"]=function(pMiner)
	pMiner:BuyAndDrinkAWhiskey()
	print("Miner"..pMiner:ID()..": That's mighty fine sippin' liquer")
	pMiner:GetFSM():ChangeState(EnterMineAndDigForNugget)  
end
QuenchThirst["Exit"]=function(pMiner)
  	print("Miner"..pMiner:ID()..": Leaving the saloon, feelin' good")
end
QuenchThirst["OnMessage"]=function(pMiner, msg)
	-- send msg to global message handler
  	return false
end
-------------------------------------------------------------------------------
-- create the EatStew state
-------------------------------------------------------------------------------
EatStew={}
EatStew["Enter"]=function(pMiner)
	print("Miner"..pMiner:ID()..": Smells Reaaal goood Elsa!")
end
EatStew["Execute"]=function(pMiner)
	print("Miner"..pMiner:ID()..": Tastes real good too!")
	pMiner:GetFSM():RevertToPreviousState()
end
EatStew["Exit"]=function(pMiner)
	print("Miner"..pMiner:ID()..": Thankya li'lle lady. Ah better get back to whatever ah wuz doin'")
end
EatStew["OnMessage"]=function(pMiner, msg)
	-- send msg to global message handler
  	return false
end

