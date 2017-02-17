function update()
    local rb = this:getComponent("Rigidbody")
    local vx, vy = rb:getVelocity()
    local velocityDesired = 0

    if getButtonPressed(this:getName().."_jump") and vy < .1 and vy > -.1 and not getButtonHeld(this:getName().."_duck") then
        rb:applyLinearImpulse(0, -8)
    end

    if getButtonHeld(this:getName().."_right") and not getButtonHeld(this:getName().."_duck") then
        velocityDesired = 5;
    end

    if getButtonHeld(this:getName().."_left") and not getButtonHeld(this:getName().."_duck") then
        velocityDesired = -5;
    end

    local velChange = velocityDesired - vx
    local impulse = rb:getMass() * velChange
    rb:applyLinearImpulse(impulse, 0)
end