const int KEY_LEFT  = 37;
const int KEY_RIGHT = 39;

float rand(float co) { return fract(sin(co*(91.3458)) * 47453.5453); }

vec2 CountCarPos(vec2 offset)
{
    float velocity = 0.01;
    
    vec2 left = texelFetch(iChannel1, ivec2(KEY_LEFT,0),0).x * vec2(-1,0);
    vec2 right = texelFetch(iChannel1, ivec2(KEY_RIGHT,0),0).x * vec2(1,0);
    
    offset += (left + right) * velocity;
    
    offset.x = max(offset.x, -0.3);
    offset.x = min(offset.x, 0.3);
    
    return offset;
}
    
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 offset = texelFetch(iChannel0, ivec2(0,0), 0).xy;
    offset = CountCarPos(offset);
    // Output to screen
    fragColor = vec4(offset, 0,0);
}
