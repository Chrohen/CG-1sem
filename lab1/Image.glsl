float sdCircle( in vec2 p, in float r )
{
    return length(p) - r;
}

float sdBox( in vec2 p, in vec2 b )
{
    vec2 d = abs(p)-b;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}

vec4 sdCar( in vec2 p, in vec2 b, in vec3 bodyCol)
{
    vec3 tireCol = vec3(0.,0.,0.);
    
    float dBody = sdBox(p, b);
    
    vec2 tireOffset = vec2 (1.35*b.x, 0.6*b.y);
    float dBLTire = sdBox(p+vec2(tireOffset * vec2(1.,1.)), b/3.);
    float dBRTire = sdBox(p+vec2(tireOffset * vec2(-1.,1.)), b/3.);
    float dFLTire = sdBox(p+vec2(tireOffset * vec2(1.,-1.)), b/3.);
    float dFRTire = sdBox(p+vec2(tireOffset * vec2(-1. ,-1.)), b/3.);
    float dTires = min(dFLTire, min(dFRTire, min(dBLTire, dBRTire)));
    
    float d = min(dBody,dTires);
    vec3 col = bodyCol;
    
    if (d == dTires)
    {
        col = tireCol;
    }
    
    return vec4(d,col);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord / iResolution.xy; 
    
    // car parameters
    vec2 center = vec2(0.5,0.15) * iResolution.xy / iResolution.y;
    vec2 p = vec2 (uv.x,uv.y) * iResolution.xy / iResolution.y;
    vec2 offset = texelFetch(iChannel0, ivec2(0,0),0).xy;
    
    center += offset;
    
    // Count distance
    vec4 car = sdCar(p-center,vec2(0.045,0.075), vec3 (1.,0.,0.));
    float d = car.x;

    // Enemy car
    vec2 ecenter = vec2(0.35,1.2) * iResolution.xy / iResolution.y;
    vec2 eoffset = texelFetch(iChannel1, ivec2(0,0),0).xy;
    
    ecenter += eoffset;
    
    // Count distance
    vec4 ecar = sdCar(p-ecenter,vec2(0.045,0.075), vec3 (0.,0.,1.));
    float ed = ecar.x;
    
    // Road
    float roadWidth = 0.4;
    vec2 roadCenter = vec2(0.5) * iResolution.xy / iResolution.y;
    vec2 pRoad = vec2 (uv.x,uv.y) * iResolution.xy / iResolution.y;
    
    float dRoad = sdBox(pRoad - roadCenter, vec2(roadWidth,1.));
	
    // coloring
    vec3 roadcol = vec3(0.4);
    
    vec2 position = vec2(int(fragCoord.x/50.0), 
        int(-(iResolution.y - fragCoord.y)/50.0 + iTime));
    
    
    if (int(position.x) % 2 == int(position.y) % 2) {
        roadcol = vec3(0.4);
    } else {
        roadcol = vec3(1.);
    }
    vec3 col = (dRoad < 0.0) ? roadcol: vec3(0.,0.7,0.);
    
    if(d<0.0)
        col = car.yzw;
    if(ed<0.0)
        col = ecar.yzw;

    // Output to screen
    fragColor = vec4(col,1.0);
}
