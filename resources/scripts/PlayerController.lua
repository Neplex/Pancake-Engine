climbing = false;

function update()
    local rb = this:getComponent("Rigidbody")
    local vx, vy = rb:getVelocity()
    local velocityYDesired = 0;
    local velocityXDesired = 0

    if getButtonPressed(this:getName().."_jump") and vy < .1 and vy > -.1 and not getButtonHeld(this:getName().."_duck") then
        if (climbing) then
            velocityYDesired = -5;
        else
            rb:applyLinearImpulse(0, -8)
        end
    end

    if getButtonHeld(this:getName().."_duck") and not getButtonHeld(this:getName().."_duck") then
        if (climbing) then
            velocityYDesired = 5;
        end
    end

    if getButtonHeld(this:getName().."_right") and not getButtonHeld(this:getName().."_duck") then
        velocityXDesired = 5;
    end

    if getButtonHeld(this:getName().."_left") and not getButtonHeld(this:getName().."_duck") then
        velocityXDesired = -5;
    end

    local velChangeY = velocityYDesired - vy
    local velChangeX = velocityXDesired - vx
    local impulseX = rb:getMass() * velChangeX
    local impulseY = rb:getMass() * velChangeY
    rb:applyLinearImpulse(impulseX, impulseY)
end
