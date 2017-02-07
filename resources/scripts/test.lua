a = 10

function changeOrigin(go)
    go:setPosition(0,0)
    go:setRotation(45)
end

function awake()
    print(a, this:getName())
    local x, y = this:getPosition()
    local r = this:getRotation()
    print(x, y, r)
    changeOrigin(this)
end

function start()
    print(a, getDeltaTime())

    local g = GameObject()

    local s = getDefaultSpriteSheet()
    s = SpriteSheet("test", "../resources/tiles_spritesheet.png", 72, 72)
    s = getSpriteSheet("test")

    local a = getDefaultAnimation()
    a = Animation("test", s)
    a = getAnimation("test")
    a:addFrame(0, 0, 200);
    a:addFrame(0, 1, 200);

    this:getComponent("SpriteRenderer"):setSprite(s, 1, 1)
    this:getComponent("Camera"):zoom(2)

    local r = this:getComponent("AnimationRenderer")
    r:setAnimation(a)
    r:loop()
    r:loop(false)
    r:play()
    r:pause()
    r:stop()
end

function update()
    if getButtonPressed("Jump") then
        print "Jump"
    end
end