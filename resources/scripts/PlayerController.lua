function update()
    local rb = this:getComponent("Rigidbody")
    local vx, vy = rb:getVelocity()
    local velocityDesired = 0

    if getButtonPressed("Jump") and vy < .1 and vy > -.1 and not getButtonHeld("Duck") then
        rb:applyLinearImpulse(0, -7)
    end

    if getButtonHeld("Right") and not getButtonHeld("Duck") then
        velocityDesired = 5;
    end

    if getButtonHeld("Left") and not getButtonHeld("Duck") then
        velocityDesired = -5;
    end

    local velChange = velocityDesired - vx
    local impulse = rb:getMass() * velChange
    rb:applyLinearImpulse(impulse, 0)
end