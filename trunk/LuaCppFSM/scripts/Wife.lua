class "Wife" (Actor)
function Wife:__init(name)
	super(name)
	print("[Wife] init is called from ".._VERSION)
	self:GetFSM():SetCurrentState(DoHouseWork)
	self:GetFSM():SetGlobalState(WifesGlobalState)
	self.m_bCooking=false
end
function Wife:__finalize()
 	print("[Wife] finalize is called from ".._VERSION)
end
function Wife:SetCooking(val)
	self.m_bCooking = val
end
function Wife:Cooking()
	return self.m_bCooking
end
-------------------------------------------------------------------------------
-- create the WifesGlobalState state
-------------------------------------------------------------------------------
WifesGlobalState={}
WifesGlobalState["Execute"]=function(wife)
  	--1 in 10 chance of needing the bathroom (provided she is not already
	--in the bathroom)
	if (math.random() < 0.1) and 
       (not(wife:GetFSM():isInState(VisitBathroom))) then
    	wife:GetFSM():ChangeState(VisitBathroom);
	end
end
WifesGlobalState["OnMessage"]=function(wife, msg)
	if msg.Msg == Msg_HiHoneyImHome then
		print("Message handled by Wife"..wife:ID().." at time: "..Clock:GetCurrentTime())
    	print("Wife"..wife:ID()..": Hi honey. Let me make you some of mah fine country stew")
		wife:GetFSM():ChangeState(CookStew)
   		return true
	end
  	return false
end
-------------------------------------------------------------------------------
-- create the DoHouseWork state
-------------------------------------------------------------------------------
DoHouseWork={}
DoHouseWork["Enter"]=function(wife)
	print("Wife"..wife:ID()..": Time to do some more housework!")
end
DoHouseWork["Execute"]=function(wife)
	local Work = math.random(0, 2)
	if Work == 0 then
		print("Wife"..wife:ID()..": Moppin' the floor")
	elseif Work == 1 then
		print("Wife"..wife:ID()..": Washin' the dishes")
	elseif Work == 2 then
    	print("Wife"..wife:ID()..": Makin' the bed")
	end
end
DoHouseWork["Exit"]=function(wife)
end
DoHouseWork["OnMessage"]=function(wife, msg)
  return false;
end
-------------------------------------------------------------------------------
-- create the VisistBathroom state
-------------------------------------------------------------------------------
VisitBathroom={}
VisitBathroom["Enter"]=function(wife)
	print("Wife"..wife:ID()..": Walkin' to the can. Need to powda mah pretty li'lle nose") 
end
VisitBathroom["Execute"]=function(wife)
  print("Wife"..wife:ID()..": Ahhhhhh! Sweet relief!")
  wife:GetFSM():RevertToPreviousState()
end
VisitBathroom["Exit"]=function(wife)
	print("Wife"..wife:ID()..": Leavin' the Jon")
end
VisitBathroom["OnMessage"]=function(wife, msg)
  return false;
end
-------------------------------------------------------------------------------
-- create the CookStew state
-------------------------------------------------------------------------------
CookStew={}
CookStew["Enter"]=function(wife)
  	-- if not already cooking put the stew in the oven
	if not(wife:Cooking()) then
    	print("Wife"..wife:ID()..": Putting the stew in the oven")
		-- send a delayed message myself so that I know when to take the stew
    	-- out of the oven
    	Dispatch:DispatchMsg(1.5,                 --time delay
        	                 wife:ID(),           --sender ID
            	             wife:ID(),           --receiver ID
                	         Msg_StewReady,       --msg
                    	     NO_ADDITIONAL_INFO) 
    	wife:SetCooking(true)
    end
end
CookStew["Execute"]=function(wife)
	print("Wife"..wife:ID()..": Fussin' over food")
end
CookStew["Exit"]=function(wife)
	-- SetTextColor(FOREGROUND_GREEN|FOREGROUND_INTENSITY);
  	print("Wife"..wife:ID()..": Puttin' the stew on the table")
end
CookStew["OnMessage"]=function(wife, msg)
		if msg.Msg == Msg_StewReady then
    	print("Message received by Wife"..wife:ID().." at time: "..Clock:GetCurrentTime())
     	print("Wife"..wife:ID()..": StewReady! Lets eat")
		-- let hubby know the stew is ready
      	Dispatch:DispatchMsg(SEND_MSG_IMMEDIATELY,
                             wife:ID(),
                             ent_Miner_Bob,
                             Msg_StewReady,
                             NO_ADDITIONAL_INFO)
      	wife:SetCooking(false)
      	wife:GetFSM():ChangeState(DoHouseWork)
    	return true
	end
	return false
end