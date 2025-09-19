float rand(float co) { return fract(sin(co*(91.3458)) * 47453.5453); }

vec2 CountCarPos(vec2 offset)
{
    float velocity = 0.6;
    
    vec2 down = texelFetch(iChannel1, ivec2(1,1),0).y * vec2(0,-1);
    
    offset.y += -(iTimeDelta) * velocity;
    
    if (offset.y < -1.5)
        offset = vec2(rand(iTime)*0.6,0);
        
    return offset;
}
    
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 offset = texelFetch(iChannel0, ivec2(0,0), 0).xy;
    offset = CountCarPos(offset);
    // Output to screen
    fragColor = vec4(offset, 0,0);
}
