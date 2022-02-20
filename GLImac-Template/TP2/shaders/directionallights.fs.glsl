#version 300 es

precision mediump float;

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform sampler2D uTexture;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

out vec3 fColor;

vec3 blinnPhong(){
    normalize(uLightDir_vs);
    normalize(vPosition_vs);
    vec3 w0 = -vPosition_vs;
    //normalize(w0);
    vec3 halfVector = (w0+uLightDir_vs)*0.5f;
    normalize(halfVector);
    normalize(vNormal_vs);
    normalize(uLightIntensity);
    normalize(uKd);
    normalize(uKs);
    
    float prodscal = dot(halfVector,vNormal_vs);
    if (prodscal < 0.0f)
    	prodscal = 0.0f;
    return (uLightIntensity*(uKd*dot(uLightDir_vs,vNormal_vs)+uKs*pow(prodscal,uShininess)));
    
}

void main(){
    vec3 colorBlinnPhong = blinnPhong();
    vec3 color;
    if (vTexCoords.x == 0.0f && vTexCoords.y == 0.0f)
    	color = vec3(0.26,0.83,0.64);
    else {
    	vec4 sortie = texture(uTexture, vTexCoords);
    	color = vec3(sortie);
    }
    
    
    normalize(colorBlinnPhong);
    normalize(color);
    fColor = colorBlinnPhong * color;
    //normalize(vNormal_vs);
    //fColor = vNormal_vs;
}
