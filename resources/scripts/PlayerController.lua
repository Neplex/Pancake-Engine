function update()
    local rb = this:getComponent("Rigidbody")
    local vx, vy = rb:getVelocity()
    local velocityDesired = 0

    if getButtonPressed("Jump") then
        rb:applyLinearImpulse(0, -5)
    end

    if getButtonHeld("Right") then
        velocityDesired = 5;
    end

    if getButtonHeld("Left") then
        velocityDesired = -5;
    end

    local velChange = velocityDesired - vx
    local impulse = rb:getMass() * velChange
    rb:applyLinearImpulse(impulse, 0)
end