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

    this:setSprite(a, 1, 1)
end

function update()
    if getButtonPressed("Jump") then
        print "Jump"
    end
end